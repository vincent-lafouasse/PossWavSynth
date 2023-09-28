#pragma once

#include <vector>
#include "cool_ints.h"

struct Wavetable
{
    static Wavetable get_square(u32 size);
    static Wavetable get_saw(u32 size);
    static Wavetable get_triangle(u32 size);
    static Wavetable get_sine(u32 size);

    float at(float pos);
    float at(u32 pos);

    std::vector<float> data;
    u32 size;
};
