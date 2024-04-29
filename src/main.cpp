#include <iostream>

#include "DSP/Signal.h"
#include "DSP/MonoSignalSmoother.hpp"
#include "midi/MidiMelody.h"
#include "midi/parse_midi.h"
#include "synth/oscillator.h"
#include "synth/wavetable.h"
#include "wav/Data.h"
#include "wav/wav.h"

#define SAMPLE_RATE 44100

struct WavetableBank
{
    Wavetable sine;
    Wavetable square;
    Wavetable triangle;
    Wavetable square8;
    Wavetable triangle8;
};

const WavetableBank wavetables = {
    Wavetables::get_sine(),
    Wavetables::get_square(),
    Wavetables::get_triangle(),
    Wavetables::band_limited_square(8),
    Wavetables::band_limited_triangle(8),
};

enum NoteStatus
{
    On,
    Off
};

class VCA
{
public:
    VCA() : level(0) {};
    VCA(float level) : level(level) {};
    float get_amplitude() { return level; };
    void set_level(float level) { this->level = level; }
    void set_level(u32 velocity) { this->level = static_cast<float>(velocity)/127; }

    float level;
};

class Synth
{
public:
    Synth() = default;
    Synth(const Wavetable* wavetable, u32 sample_rate)
    {
        osc = Oscillator(wavetable, sample_rate);
    }
    Signal realize(const MidiMelody& melody);

    Oscillator osc;
    VCA vca;
};

#include <cmath>
float f_12tet(u32 note)
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

int main()
{
    /*
    Oscillator osc_s(&wavetables.triangle8, SAMPLE_RATE);
    Oscillator osc_a(&wavetables.square8, SAMPLE_RATE);
    Oscillator osc_t(&wavetables.triangle8, SAMPLE_RATE);
    Oscillator osc_b(&wavetables.square8, SAMPLE_RATE);

    Signal soprano(soprano_melody(), &osc_s);
    Signal alto(alto_melody(), &osc_a);
    Signal tenor(tenor_melody(), &osc_t);
    Signal bass(bass_melody(), &osc_b);

    Signal signal = Signal::sum({
        std::make_pair(soprano, 1),
        std::make_pair(alto, 1),
        std::make_pair(tenor, 1),
        std::make_pair(bass, 1),
    });
    */

    std::vector<MidiMelody> voices = parse_midi("./mid/licc.mid");

    for (MidiMelody& melody: voices)
         melody.quantize(SAMPLE_RATE);

    Synth square(&wavetables.square8, SAMPLE_RATE);

    Signal signal = square.realize(voices[0]);
    // signal.write_to_csv();

    Data32 data(signal, SAMPLE_RATE);

    WavFile wav_file(data);

    const char* status = wav_file.write("wave.wav") ? "success" : "rip";
    std::cout << status << std::endl;
}

/*
Melody a_cool_melody(void)
{
    constexpr float tempo_bpm = 120.0f;
    constexpr float quarter_note_sec = (60.0f / tempo_bpm);
    constexpr float eigth_triplet_sec = (quarter_note_sec / 3.0f);

    const float g4_frequency = get_frequency(4, 7);
    const float a4_frequency = get_frequency(4, 9);
    const float b4_frequency = get_frequency(4, 11);
    const float c5_frequency = get_frequency(5, 0);
    const float d5_frequency = get_frequency(5, 2);

    Melody melody;
    melody.add_note(a4_frequency, 2 * eigth_triplet_sec);
    melody.add_note(b4_frequency, 1 * eigth_triplet_sec);
    melody.add_note(c5_frequency, 2 * eigth_triplet_sec);
    melody.add_note(d5_frequency, 1 * eigth_triplet_sec);
    melody.add_note(b4_frequency, 3 * eigth_triplet_sec);
    melody.add_note(g4_frequency, 2 * eigth_triplet_sec);
    melody.add_note(a4_frequency, 4 * eigth_triplet_sec);

    return melody;
}
*/
