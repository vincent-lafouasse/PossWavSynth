#include <iostream>

#include "cool_ints.h"
#include "data.h"
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

int main()
{
    Wavetable sine_wavetable = Wavetable::get_sine(WAVETABLE_RESOLUTION);
    Oscillator sine_wave = Oscillator::init(&sine_wavetable, SAMPLE_RATE);
    sine_wave.set_frequency(440.0f / 1.5f);

    float n_seconds = 2;
    u32 n_samples = SAMPLE_RATE * n_seconds * N_CHANNELS;

    FloatData float_data(n_samples);

    for (u32 i = 0; i < n_samples; i++)
    {
        float_data.data[i] = sine_wave.get();
        sine_wave.advance();
        if (i == n_samples / 2)
            sine_wave.set_frequency(440.0f);
    }

    Data<SAMPLE_TYPE> data(&float_data, BIT_DEPTH, SAMPLE_IS_SIGNED);

    WavHeader header = WavHeader::init(n_samples * (BIT_DEPTH / 8), N_CHANNELS,
                                       SAMPLE_RATE, BIT_DEPTH);

    WavFile wav_file = WavFile::init("wave.wav", &header, data.data);

    if (wav_file.write())
        std::cout << "success" << std::endl;
    else
        std::cout << "rip" << std::endl;
}
