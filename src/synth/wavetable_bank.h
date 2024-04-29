#pragma once

#include "wavetable.h"

struct WavetableBank
{
    Wavetable sine;
    Wavetable square;
    Wavetable triangle;
    Wavetable square8;
    Wavetable triangle8;
};

const WavetableBank wavetables = {
    Wavetables::get_sine(),
    Wavetables::get_square(),
    Wavetables::get_triangle(),
    Wavetables::band_limited_square(8),
    Wavetables::band_limited_triangle(8),
};
