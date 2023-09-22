#pragma once

#include "cool_ints.h"
#include "wavetable.h"

struct Oscillator
{
    static Oscillator init(Wavetable* wavetable, u32 sample_rate);
    void set_frequency(float f);
    float get(void);
    void advance(void);

    Wavetable* wavetable;
    u32 sample_rate;
    float frequency;
    float phase;
    float increment;
};
