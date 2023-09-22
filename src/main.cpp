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
    float at(u32 pos);

    std::vector<float> data;
    u32 size;
};

Wavetable Wavetable::get_square(u32 size)
{
    Wavetable w;
    float sample;

    w.size = size;

    w.data.reserve(size);
    for (u32 i = 0; i < size; i++)
    {
        sample = (i < size / 2) ? 1.0f : -1.0f;
        w.data.push_back(sample);
    }

    return w;
}

float positive_frac_part(float f)
{
    f = f - (int)f;
    f += (f < 0);
    return f;
}

float Wavetable::at(u32 pos)
{
    pos = pos % size;
    return data.at(pos);
}

float Wavetable::at(float pos)
{
    pos = positive_frac_part(pos);

    float float_index = pos * size;
    u32 lower_index = float_index;
    u32 upper_index = lower_index + 1;

    float lower_contribution = (float_index - lower_index) * at(lower_index);
    float upper_contribution = (upper_index - float_index) * at(upper_index);

    return lower_contribution + upper_contribution;
}

struct Oscillator
{
    static Oscillator init(Wavetable* wavetable, u32 sample_rate);
    void set_frequency(float f);
    float next(void);

    Wavetable* wavetable;
    u32 sample_rate;
    float frequency;
    float phase;
    float increment;
};

Oscillator Oscillator::init(Wavetable* wavetable, u32 sample_rate)
{
    Oscillator o;

    o.wavetable = wavetable;
    o.sample_rate = sample_rate;
    o.phase = 0.0f;
    o.set_frequency(440.0f);

    return o;
}

void Oscillator::set_frequency(float f)
{
    frequency = f;
    increment = f / sample_rate;
}

void fill_data(i32* data, i32 size);

int main()
{
    Wavetable square_wavetable = Wavetable::get_square(WAVETABLE_RESOLUTION);
    Oscillator square_wave = Oscillator::init(&square_wavetable, SAMPLE_RATE);
    square_wave.set_frequency(440.0f);
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
