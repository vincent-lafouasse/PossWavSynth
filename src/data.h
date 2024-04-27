#pragma once

#include <fstream>

#include "cool_ints.h"
#include "melody.h"
#include "oscillator.h"

struct Signal
{
    Signal(Melody* melody, Oscillator* oscillator);
    Signal(u32 size_);
    ~Signal();

    void write_to_csv(void);
    void normalize(void);

    float* data;
    u32 size;
};

template <typename T>
struct Data
{
    Data();
    Data(Signal* float_data, u32 bit_depth_, bool sample_is_signed);
    ~Data();

    void write_to_csv(void);

    T* data;
    u32 size;
    u32 bit_depth;
};

template <typename T>
static T clamp(T item, T min, T max);

template <typename T>
static T max_binary_value(u32 bit_depth, bool sample_is_signed);

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
Data<T>::Data(Signal* float_data, u32 bit_depth_, bool sample_is_signed)
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

template <typename T>
static T clamp(T item, T min, T max)
{
    if (item > max)
        item = max;
    if (item < min)
        item = min;
    return item;
}

template <typename T>
static T max_binary_value(u32 bit_depth, bool sample_is_signed)
{
    u32 actual_bit_depth = bit_depth - sample_is_signed;
    u64 out = (1 << actual_bit_depth) - 1;
    return out;
}
