#include <iostream>

#include "cool_ints.h"
#include "wav.h"

int main()
{
    int sample_rate = 44100;
    int n_channels = 1;
    int n_seconds = 4;

    i32 data_size = sample_rate * n_seconds * n_channels;
    i32* data = new int[data_size];
    u16 bit_depth = 32;

    i32 frequency = 440;

    i32 period = sample_rate / frequency;

    i32 sample_value = 0;
    for (int i = 0; i < data_size; i++)
    {
        if (i % period == 0)
            sample_value = 0;
        data[i] = sample_value;
        sample_value += 8000;
        std::cout << sample_value << std::endl;
    }

    WavHeader header = WavHeader::init(data_size * bit_depth, n_channels,
                                       sample_rate, bit_depth);

    WavFile wav_file = WavFile::init("wave.wav", &header, data);

    if (wav_file.write())
        std::cout << "success" << std::endl;
    else
        std::cout << "rip" << std::endl;

    delete[] data;
}
