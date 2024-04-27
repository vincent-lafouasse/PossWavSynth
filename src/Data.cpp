#include "Data.h"

template <typename T>
static T clamp(T item, T min, T max);

Data32::Data32()
{
    this->data = nullptr;
    this->size = 0;
    this->sample_rate = 0;
    this->bit_depth = 32;
}

Data32::Data32(Signal& signal, u32 sample_rate)
{
    this->sample_rate = sample_rate;
    this->bit_depth = 32;
    this->size = signal.size;
    
    data = new i32[signal.size];

    signal.normalize();
    for (u32 i = 0; i < size; i++)
        data[i]= static_cast<u32>(INT32_MAX * signal.data[i]);
}

void Data32::write(FILE* file)
{
    printf("writing");
    (void)file;
}

Data32::~Data32()
{
    delete[] data;
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
