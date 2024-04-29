#include "Synth.h"
#include <cmath>
#include <cassert>
#include "DSP/MonoSignalSmoother.hpp"
#include "midi/MidiMelody.h"

static float f_12tet(u32 note)
{
    i32 offset_from_a4 = note - 69;
    float f_offset = static_cast<float>(offset_from_a4);

    return 440.0 * std::exp2(f_offset / 12.0);
}

Signal Synth::realize(const MidiMelody& melody)
{
    assert(melody.messages.back().status == NoteOff);
    std::vector<Message> messages = melody.messages;
    u32 signal_size = messages.back().timestamp_quantized;

    u32 last_update = 0;
    MessageStatus status;

    auto msg = messages.cbegin();

    MonoSignalSmoother<float> smoothed_amplitude(0.7);

    Signal out(signal_size);

    for (u32 tick = 0; tick < out.size; tick++)
    {
        while (msg != messages.cend() && msg->timestamp_quantized <= tick)
        {
            if (msg->status == NoteOn)
            {
                osc.set_frequency(f_12tet(msg->note));
                vca.set_level(msg->velocity);
                last_update = tick;
                status = msg->status;
            }
            if (msg->status == NoteOff)
            {
                vca.set_level(0.0f);
                last_update = tick;
                status = msg->status;
            }
            msg++;
        }

        float new_target_amp = vca.get_amplitude(status, last_update - tick);
        smoothed_amplitude.set_target(new_target_amp);
        float effective_amp = smoothed_amplitude.get();

        out.data[tick] = effective_amp * osc.get();
        osc.advance();
    }

    return out;
}
