#pragma once
#include "melody.h"

#include "oscillator.h"

struct Signal
{
    Signal(Melody* melody, Oscillator* oscillator);
    Signal(u32 size_);
    ~Signal();

    static Signal sum(const Signal& s1, const Signal& s2);

    void write_to_csv(void);
    void normalize(void);

    float* data;
    u32 size;
};
