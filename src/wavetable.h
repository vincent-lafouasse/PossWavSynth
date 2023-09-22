#pragma once

#include <vector>
#include "cool_ints.h"

struct Wavetable
{
    static Wavetable get_square(u32 size);
    float at(float pos);
    float at(u32 pos);

    std::vector<float> data;
    u32 size;
};
