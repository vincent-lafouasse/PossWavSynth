#include "Data.h"

Data32::Data32()
{
    this->data = nullptr;
}

Data32::Data32(Signal& signal, u32 sample_rate)
{
    this->sample_rate = sample_rate;
    bit_depth = 32;
    sample_size_byte = sizeof(i32);
    size = signal.size;

    data = new i32[signal.size];

    constexpr float headroom = 0.9f;

    signal.normalize();
    for (u32 i = 0; i < size; i++)
        data[i] = static_cast<i32>(INT32_MAX * headroom * signal.data[i]);
}

void Data32::write(FILE* file, u32 max_bytes) const
{
    printf("writing data to disk\n");
    u32 max_n = std::min<u32>(size, max_bytes / sample_size_byte);

    for (u32 i = 0; i < max_n; i++)
        fwrite(data + i, sample_size_byte, 1, file);
}

void Data32::write_csv(const char* name) const
{
    FILE* csv = fopen(name, "w");

    for (u32 i = 0; i < size - 1; i++)
        fprintf(csv, "");
}

Data32::~Data32()
{
    delete[] data;
}
