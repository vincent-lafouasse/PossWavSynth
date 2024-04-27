#pragma once

#include <vector>
#include "cool_ints.h"

struct Wavetable
{
    float at(float pos) const;
    float at(u32 pos) const;
    void normalize(void);

    void write_to_csv(const std::string& output_filename);

    std::vector<float> data;
    u32 size;
};

namespace Wavetables
{
    Wavetable get_empty();
    Wavetable get_sine();
    Wavetable get_square();
    Wavetable get_saw();
    Wavetable get_triangle();
    Wavetable get_harmonic(u32 multiplier);
    Wavetable a_cool_additive_wavetable(void);
}

struct Harmonic
{
    Harmonic(float multiplier, float amplitude);
    u32 multiplier;
    float amplitude;
};

struct AdditiveWavetableFactory
{
    AdditiveWavetableFactory();

    Wavetable get();
    void add_harmonic(u32 multiplier, float amplitude);

    std::vector<Harmonic> harmonics;
};

