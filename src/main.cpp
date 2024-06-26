#include <iostream>

#include "DSP/Signal.h"
#include "midi/MidiMelody.h"
#include "midi/parse_midi.h"
#include "synth/Synth.h"
#include "synth/wavetable_bank.h"
#include "wav/Data.h"
#include "wav/wav.h"

#define SAMPLE_RATE 44100

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

    for (MidiMelody& melody : voices)
        melody.quantize(SAMPLE_RATE);

    Synth square(&wavetables.square8, SAMPLE_RATE);

    Signal signal = square.realize(voices[0]);
    signal.write_to_csv();

    // serializing data
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
