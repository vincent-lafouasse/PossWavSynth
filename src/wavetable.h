#pragma once

#include <vector>
#include "cool_ints.h"

struct Wavetable
{
    static Wavetable get_square(u32 size);
    static Wavetable get_saw(u32 size);
    static Wavetable get_triangle(u32 size);
    static Wavetable get_sine(u32 size);
    static Wavetable get_harmonic(u32 multiplier, u32 size);

    static Wavetable get_empty(u32 size);

    float at(float pos);
    float at(u32 pos);
    void normalize(void);

    void write_to_csv(std::string name);

    std::vector<float> data;
    u32 size;
};

struct Harmonic
{
    Harmonic(u32 multiplier_, float amplitude_);
    u32 multiplier;
    float amplitude;
};

struct AdditiveWavetableFactory
{
    AdditiveWavetableFactory();

    Wavetable get(u32 size);
    void add_harmonic(u32 multiplier, float amplitude);

    std::vector<Harmonic> harmonics;
};
