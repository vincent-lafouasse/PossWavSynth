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

    float at(float pos);
    float at(u32 pos);
    void normalize(void);

    void write_to_csv(const std::string& output_filename);

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

    Wavetable get();
    void add_harmonic(u32 multiplier, float amplitude);

    std::vector<Harmonic> harmonics;
};
