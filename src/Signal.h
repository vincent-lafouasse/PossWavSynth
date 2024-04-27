#pragma once
#include "melody.h"

#include <vector>

#include "oscillator.h"

struct Signal
{
    Signal(const Melody& melody, Oscillator* oscillator);
    Signal(u32 size_);
    ~Signal();

    static Signal sum(const Signal& s1,
                      const Signal& s2,
                      float amp1,
                      float amp2);
    static Signal sum(const std::vector<std::pair<const Signal&, float>>& signals);

    void write_to_csv(void);
    void normalize(void);

    float* data;
    u32 size;
};
