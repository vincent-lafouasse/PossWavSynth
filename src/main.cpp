#include <iostream>
#include <vector>

#include "cool_ints.h"
#include "wav.h"

#define SAMPLE_RATE 44100
#define N_CHANNELS 1

#define WAVETABLE_RESOLUTION 1024

#define SAMPLE_TYPE i32
#define BIT_DEPTH 8 * sizeof(SAMPLE_TYPE)

struct Wavetable
{
    static Wavetable get_square(u32 size);
    float at(float pos);

    std::vector<float> data;
};

Wavetable Wavetable::get_square(u32 size)
{
    Wavetable w;
    float sample;

    w.data.reserve(size);
    for (u32 i = 0; i < size; i++)
    {
        sample = (i < size / 2) ? 1.0f : -1.0f;
        w.data.push_back(sample);
    }

    return w;
}

struct Oscillator
{
    static Oscillator init(Wavetable* wavetable,
                           u32 sample_rate,
                           float frequency);
    Wavetable* wavetable;
    u32 sample_rate;
    float frequency;
    float phase;
};

Oscillator Oscillator::init(Wavetable* wavetable,
                            u32 sample_rate,
                            float frequency)
{
    Oscillator o;

    o.wavetable = wavetable;
    o.sample_rate = sample_rate;
    o.frequency = frequency;
    o.phase = 0.0f;

    return o;
}

void fill_data(i32* data, i32 size);

int main()
{
    Wavetable square_wavetable = Wavetable::get_square(WAVETABLE_RESOLUTION);
    Oscillator square_wave =
        Oscillator::init(&square_wavetable, SAMPLE_RATE, 440.0f);
    int n_seconds = 4;

    i32 n_samples = SAMPLE_RATE * n_seconds * N_CHANNELS;

    i32* data = new int[n_samples];
    fill_data(data, n_samples);

    WavHeader header = WavHeader::init(n_samples * (BIT_DEPTH / 8), N_CHANNELS,
                                       SAMPLE_RATE, BIT_DEPTH);

    WavFile wav_file = WavFile::init("wave.wav", &header, data);

    if (wav_file.write())
        std::cout << "success" << std::endl;
    else
        std::cout << "rip" << std::endl;

    delete[] data;
}

void fill_data(i32* data, i32 size)
{
    i32 sample_value = 0;
    for (int i = 0; i < size; i++)
    {
        sample_value += 8000000;
        data[i] = sample_value;
    }
}
