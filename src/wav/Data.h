#pragma once

#include <cstdio>

#include "DSP/Signal.h"

class Data
{
   public:
    virtual void write(FILE* file, u32 max_bytes) const = 0;
    virtual void write_csv(const char* name) const = 0;

    u32 size;
    u32 sample_rate;
    u32 sample_size_byte;
    u16 bit_depth;
};

class Data32 : public Data
{
   public:
    Data32();
    Data32(Signal& signal, u32 sample_rate);
    ~Data32();
    void write(FILE* file, u32 max_bytes) const;
    void write_csv(const char* name) const;

    i32* data;
};
