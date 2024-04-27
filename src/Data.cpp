#include "Data.h"

Data32::Data32()
{
    this->data = nullptr;
}

Data32::Data32(Signal& signal, u32 sample_rate)
{
    this->sample_rate = sample_rate;
    bit_depth = 32;
    sample_size_byte = sizeof(u32);
    size = signal.size;

    data = new i32[signal.size];

    signal.normalize();
    for (u32 i = 0; i < size; i++)
        data[i] = static_cast<u32>(INT32_MAX * signal.data[i]);
}

void* Data32::get() const
{
    return static_cast<void*>(data);
}

void Data32::write(FILE* file) const
{
    printf("writing");
    (void)file;
}

Data32::~Data32()
{
    delete[] data;
}
