#include <fstream>
#include <iostream>

#include "cool_ints.h"
#include "oscillator.h"
#include "wav.h"
#include "wavetable.h"

#define PRINT(expr) std::cout << +expr << std::endl;

#define SAMPLE_RATE 44100
#define N_CHANNELS 1

#define WAVETABLE_RESOLUTION 1024

// do not use u64
#define SAMPLE_TYPE u8
#define BIT_DEPTH 7
#define SAMPLE_IS_SIGNED false

template <typename T>
T clamp(T item, T min, T max)
{
    if (item > max)
        item = max;
    if (item < min)
        item = min;
    return item;
}

struct FloatData
{
    FloatData(u32 size_);
    ~FloatData();

    void write_to_csv(void);
    void normalize(void);

    float* data;
    u32 size;
};

FloatData::FloatData(u32 size_)
{
    size = size_;
    data = new float[size];

    for (u32 i = 0; i < size; i++)
        data[i] = 0.0f;
}

FloatData::~FloatData()
{
    delete[] data;
}

void FloatData::write_to_csv(void)
{
    std::ofstream csv;
    csv.open("float_data.csv");
    for (u32 i = 0; i < size; i++)
    {
        csv << data[i] << ",";
    }
    csv << std::endl;
    csv.close();
}

void FloatData::normalize(void) {}

template <typename T>
struct Data
{
    Data();
    Data(FloatData* float_data, u32 bit_depth_, bool sample_is_signed);
    ~Data();

    void write_to_csv(void);

    T* data;
    u32 size;
    u32 bit_depth;
};

template <typename T>
Data<T>::Data()
{
    data = nullptr;
    size = 0;
    bit_depth = 0;
}

template <typename T>
Data<T>::~Data()
{
    if (data == nullptr)
        return;

    delete[] data;
}

template <typename T>
T max_binary_value(u32 bit_depth, bool sample_is_signed)
{
    u32 actual_bit_depth = bit_depth - sample_is_signed;
    u64 out = (1 << actual_bit_depth) - 1;
    return out;
}

template <typename T>
Data<T>::Data(FloatData* float_data, u32 bit_depth_, bool sample_is_signed)
{
    size = float_data->size;
    data = new T[size];
    float_data->normalize();

    bit_depth = bit_depth_;
    T max = max_binary_value<T>(bit_depth_, sample_is_signed);
    T min = sample_is_signed * (-max);

    for (u32 i = 0; i < size; i++)
    {
        data[i] = (T)(!sample_is_signed + (float_data->data[i]) * (float)max);
        data[i] = clamp<T>(data[i], min, max);
    }

    std::cout << +min << std::endl;
    std::cout << +max << std::endl;
}

template <typename T>
void Data<T>::write_to_csv(void)
{
    std::ofstream csv;
    csv.open("int_data.csv");
    for (u32 i = 0; i < size; i++)
    {
        csv << +data[i] << ",";
    }
    csv << std::endl;
    csv.close();
}

void fill_data(i32* data, i32 size, Oscillator* oscillator);

int main()
{
    Wavetable square_wavetable = Wavetable::get_square(WAVETABLE_RESOLUTION);
    Oscillator square_wave = Oscillator::init(&square_wavetable, SAMPLE_RATE);
    square_wave.set_frequency(440.0f);

    float n_seconds = 0.02;
    u32 n_samples = SAMPLE_RATE * n_seconds * N_CHANNELS;

    FloatData float_data(n_samples);

    for (u32 i = 0; i < n_samples; i++)
    {
        float_data.data[i] = square_wave.get();
        square_wave.advance();
    }

    float_data.normalize();

    float_data.write_to_csv();

    Data<SAMPLE_TYPE> data_(&float_data, BIT_DEPTH, SAMPLE_IS_SIGNED);
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
