#pragma once

#include <fstream>

#include "Signal.h"
#include "cool_ints.h"

template <typename T>
struct WavData
{
    WavData();
    WavData(Signal* float_data, u32 bit_depth_, bool sample_is_signed);
    ~WavData();

    void write_binary(FILE* file, u32 buffer_size_bytes);
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
WavData<T>::WavData()
{
    data = nullptr;
    size = 0;
    bit_depth = 0;
}

template <typename T>
WavData<T>::~WavData()
{
    if (data == nullptr)
        return;

    delete[] data;
}

template <typename T>
WavData<T>::WavData(Signal* float_data, u32 bit_depth_, bool sample_is_signed)
{
    size = float_data->size;
    data = new T[size];
    float_data->normalize();

    bit_depth = bit_depth_;
    T max = max_binary_value<T>(bit_depth_, sample_is_signed);
    T min = sample_is_signed ? -max : 0;

    for (u32 i = 0; i < size; i++)
    {
        data[i] = (T)(!sample_is_signed + (float_data->data[i]) * (float)max);
        data[i] = clamp<T>(data[i], min, max);
    }
}

template <typename T>
void WavData<T>::write_to_csv(void)
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
        return max;
    if (item < min)
        return min;
    return item;
}

template <typename T>
static T max_binary_value(u32 bit_depth, bool sample_is_signed)
{
    u32 actual_bit_depth = bit_depth - sample_is_signed;
    u64 out = (1 << actual_bit_depth) - 1;
    return out;
}
