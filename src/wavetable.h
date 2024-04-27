#pragma once

#include <vector>
#include "cool_ints.h"

struct Wavetable
{
    static Wavetable get_square();
    static Wavetable get_saw();
    static Wavetable get_triangle();
    static Wavetable get_sine();
    static Wavetable get_harmonic(u32 multiplier);

    static Wavetable get_empty();

    float at(float pos) const;
    float at(u32 pos) const;
    void normalize(void);

    void write_to_csv(const std::string& output_filename);

    std::vector<float> data;
    u32 size;
};

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

Wavetable a_cool_additive_wavetable(void);
