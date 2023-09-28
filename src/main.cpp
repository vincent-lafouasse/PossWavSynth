#include <iostream>
#include <vector>

#include "cool_ints.h"
#include "data.h"
#include "melody.h"
#include "oscillator.h"
#include "wav.h"
#include "wavetable.h"

#define SAMPLE_RATE 44100
#define N_CHANNELS 1

#define WAVETABLE_RESOLUTION 1024

// do not use u64
#define SAMPLE_TYPE i32
#define BIT_DEPTH 32
#define SAMPLE_IS_SIGNED true

#define G4 get_frequency(4, 7)
#define A4 get_frequency(4, 9)
#define B4 get_frequency(4, 11)
#define C5 get_frequency(5, 0)
#define D5 get_frequency(5, 2)
#define REST 0.0f

#define TEMPO_BPM 120.0f
#define QUARTER_NOTE_SEC (60.0f / TEMPO_BPM)
#define EIGTH_TRIPLET_SEC (QUARTER_NOTE_SEC / 3.0f)

int main()
{
    Melody melody;
    melody.add_note(A4, 2 * EIGTH_TRIPLET_SEC);
    melody.add_note(B4, 1 * EIGTH_TRIPLET_SEC);
    melody.add_note(C5, 2 * EIGTH_TRIPLET_SEC);
    melody.add_note(D5, 1 * EIGTH_TRIPLET_SEC);
    melody.add_note(B4, 3 * EIGTH_TRIPLET_SEC);
    melody.add_note(G4, 2 * EIGTH_TRIPLET_SEC);
    melody.add_note(A4, 4 * EIGTH_TRIPLET_SEC);

    AdditiveWavetableFactory additive_factory;
    additive_factory.add_harmonic(2, 0.5f);

    Wavetable additive_wavetable = additive_factory.get(SAMPLE_RATE);

    Wavetable* wavetable_ptr = &additive_wavetable;

    Oscillator oscillator = Oscillator::init(wavetable_ptr, SAMPLE_RATE);

    u32 n_samples = melody.get_total_n_samples(SAMPLE_RATE) * N_CHANNELS;

    FloatData float_data(&melody, &oscillator);

    Data<SAMPLE_TYPE> data(&float_data, BIT_DEPTH, SAMPLE_IS_SIGNED);

    WavHeader header = WavHeader::init(n_samples * (BIT_DEPTH / 8), N_CHANNELS,
                                       SAMPLE_RATE, BIT_DEPTH);

    WavFile wav_file = WavFile::init("wave.wav", &header, data.data);

    if (wav_file.write())
        std::cout << "success" << std::endl;
    else
        std::cout << "rip" << std::endl;
}
