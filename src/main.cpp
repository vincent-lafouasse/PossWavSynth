#include <iostream>

#include "cool_ints.h"
#include "wav.h"
#include "wavetable.h"

#define SAMPLE_RATE 44100
#define N_CHANNELS 1

#define WAVETABLE_RESOLUTION 1024

#define SAMPLE_TYPE i32
#define BIT_DEPTH 8 * sizeof(SAMPLE_TYPE)

struct Oscillator
{
    static Oscillator init(Wavetable* wavetable, u32 sample_rate);
    void set_frequency(float f);
    float get(void);
    void advance(void);

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

float Oscillator::get()
{
    return wavetable->at(phase);
}

void Oscillator::advance()
{
    phase += increment;
    phase -= (phase >= 1.0f);
}

void fill_data(i32* data, i32 size, Oscillator* oscillator);

int main()
{
    Wavetable square_wavetable = Wavetable::get_square(WAVETABLE_RESOLUTION);
    Oscillator square_wave = Oscillator::init(&square_wavetable, SAMPLE_RATE);
    square_wave.set_frequency(440.0f);
    int n_seconds = 4;

    i32 n_samples = SAMPLE_RATE * n_seconds * N_CHANNELS;

    i32* data = new int[n_samples];
    fill_data(data, n_samples, &square_wave);

    WavHeader header = WavHeader::init(n_samples * (BIT_DEPTH / 8), N_CHANNELS,
                                       SAMPLE_RATE, BIT_DEPTH);

    WavFile wav_file = WavFile::init("wave.wav", &header, data);

    if (wav_file.write())
        std::cout << "success" << std::endl;
    else
        std::cout << "rip" << std::endl;

    delete[] data;
}

void fill_data(i32* data, i32 size, Oscillator* oscillator)
{
    for (int i = 0; i < size; i++)
    {
        data[i] = oscillator->get();
        oscillator->advance();
    }
}
