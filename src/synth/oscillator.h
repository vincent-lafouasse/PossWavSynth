#pragma once

#include "utils/cool_ints.h"
#include "wavetable.h"

struct Oscillator
{
    Oscillator() = default;
    Oscillator(const Wavetable* wavetable, u32 sample_rate);
    void set_frequency(float f);
    float get(void);
    void advance(void);

    const Wavetable* wavetable;
    u32 sample_rate;
    float frequency;
    float phase;
    float increment;
};
