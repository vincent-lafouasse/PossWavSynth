#pragma once

#include <cstdio>

#include "Signal.h"

class Data
{
public:
    virtual void write(FILE* file) = 0;

    u32 size;
    u32 sample_rate;
    u16 bit_depth;
    bool signedness;
};

class Data32: public Data
{
public:
    Data32();
    Data32(Signal& signal, u32 sample_rate);
    ~Data32();
    void write(FILE* file);

    i32* data;
};
