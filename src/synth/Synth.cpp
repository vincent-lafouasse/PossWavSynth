#include "Synth.h"
#include "DSP/MonoSignalSmoother.hpp"
#include <cmath>

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
            }
            if (msg->status == NoteOff)
            {
                vca.set_level(0.0f);
            }
            msg++;
        }

        smoothed_amplitude.set_target(vca.get_amplitude());
        
        out.data[tick] = smoothed_amplitude.get() * osc.get();
        osc.advance();
    }

    return out;
}
