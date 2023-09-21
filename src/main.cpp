#include <iostream>

#include "cool_ints.h"
#include "wav.h"

#define SAMPLE_RATE 44100
#define N_CHANNELS 1

#define SAMPLE_TYPE i32
#define BIT_DEPTH 8 * sizeof(SAMPLE_TYPE)

void fill_data(i32* data, i32 size);

int main()
{
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
