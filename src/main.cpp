#include <iostream>

#include "Data.h"
#include "Signal.h"
#include "melody.h"
#include "oscillator.h"
#include "wav.h"
#include "wavetable.h"

#define SAMPLE_RATE 44100

static Melody a_cool_melody(void);

int main()
{
    Melody melody = a_cool_melody();

    Wavetable triangle_wave = Wavetable::get_triangle();
    Oscillator oscillator(&triangle_wave, SAMPLE_RATE);

    Signal signal(&melody, &oscillator);

    Data32 data(signal, SAMPLE_RATE);

    WavFile wav_file(data);

    const char* status = wav_file.write("wave.wav") ? "success" : "rip";
    std::cout << status << std::endl;
}

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
