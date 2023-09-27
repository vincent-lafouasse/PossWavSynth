#include <fstream>
#include <iostream>

#include "cool_ints.h"
#include "oscillator.h"
#include "wav.h"
#include "wavetable.h"

#define SAMPLE_RATE 44100
#define N_CHANNELS 1

#define WAVETABLE_RESOLUTION 1024

#define SAMPLE_TYPE i32
#define BIT_DEPTH 8 * sizeof(SAMPLE_TYPE)

struct Data
{
    Data(u32 size_);
    ~Data();

    void write_to_csv(void);
    void normalize(void);

    float* data;
    u32 size;
};

Data::Data(u32 size_)
{
    size = size_;
    data = new float[size];

    for (u32 i = 0; i < size; i++)
        data[i] = 0.0f;
}

Data::~Data()
{
    delete[] data;
}

void Data::write_to_csv(void)
{
    std::ofstream csv;
    csv.open("data.csv");
    for (u32 i = 0; i < size; i++)
    {
        csv << data[i] << ",";
    }
    csv << std::endl;
    csv.close();
}

void Data::normalize(void) {}

void fill_data(i32* data, i32 size, Oscillator* oscillator);

int main()
{
    Wavetable square_wavetable = Wavetable::get_square(WAVETABLE_RESOLUTION);
    Oscillator square_wave = Oscillator::init(&square_wavetable, SAMPLE_RATE);
    square_wave.set_frequency(440.0f);

    int n_seconds = 2;
    u32 n_samples = SAMPLE_RATE * n_seconds * N_CHANNELS;

    Data data_(n_samples);

    for (u32 i = 0; i < n_samples; i++)
    {
        data_.data[i] = square_wave.get();
        square_wave.advance();
    }

    data_.normalize();

    data_.write_to_csv();

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
