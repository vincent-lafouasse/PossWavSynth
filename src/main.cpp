#include <iostream>

#include "Signal.h"
#include "WavData.hpp"
#include "cool_ints.h"
#include "melody.h"
#include "oscillator.h"
#include "wav.h"
#include "wavetable.h"

#define SAMPLE_RATE 44100
#define N_CHANNELS 1

// do not use u64
#define SAMPLE_TYPE i32
#define BIT_DEPTH 32
#define SAMPLE_IS_SIGNED true

#define TEMPO_BPM 120.0f
#define QUARTER_NOTE_SEC (60.0f / TEMPO_BPM)
#define EIGTH_TRIPLET_SEC (QUARTER_NOTE_SEC / 3.0f)

class Sample
{
   public:
    u16 bit_depth;
    bool is_signed;
};

class Sample32Bit : Sample
{
   public:
    i32 data;
};

Melody a_cool_melody(void);
Wavetable a_cool_additive_wavetable(void);

int main()
{
    Melody melody = a_cool_melody();

    Wavetable additive_wavetable = a_cool_additive_wavetable();
    Oscillator oscillator = Oscillator::init(&additive_wavetable, SAMPLE_RATE);

    u32 n_samples = melody.get_total_n_samples(SAMPLE_RATE) * N_CHANNELS;

    Sample foo;
    foo.is_signed = false;

    Sample32Bit bar;
    bar.data = -34;

    Signal buffer(&melody, &oscillator);

    WavData<SAMPLE_TYPE> data(&buffer, BIT_DEPTH, SAMPLE_IS_SIGNED);

    WavHeader header = WavHeader::init(n_samples * (BIT_DEPTH / 8), N_CHANNELS,
                                       SAMPLE_RATE, BIT_DEPTH);

    WavFile wav_file = WavFile::init("wave.wav", &header, data.data);

    if (wav_file.write())
        std::cout << "success" << std::endl;
    else
        std::cout << "rip" << std::endl;
}

Melody a_cool_melody(void)
{
    const float g4_frequency = get_frequency(4, 7);
    const float a4_frequency = get_frequency(4, 9);
    const float b4_frequency = get_frequency(4, 11);
    const float c5_frequency = get_frequency(5, 0);
    const float d5_frequency = get_frequency(5, 2);

    Melody melody;
    melody.add_note(a4_frequency, 2 * EIGTH_TRIPLET_SEC);
    melody.add_note(b4_frequency, 1 * EIGTH_TRIPLET_SEC);
    melody.add_note(c5_frequency, 2 * EIGTH_TRIPLET_SEC);
    melody.add_note(d5_frequency, 1 * EIGTH_TRIPLET_SEC);
    melody.add_note(b4_frequency, 3 * EIGTH_TRIPLET_SEC);
    melody.add_note(g4_frequency, 2 * EIGTH_TRIPLET_SEC);
    melody.add_note(a4_frequency, 4 * EIGTH_TRIPLET_SEC);

    return melody;
}

Wavetable a_cool_additive_wavetable(void)
{
    AdditiveWavetableFactory additive_factory;
    additive_factory.add_harmonic(2, 0.5f);
    additive_factory.add_harmonic(5, 0.25f);

    return additive_factory.get();
}
