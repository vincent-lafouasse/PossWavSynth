#include "Synth.h"
#include <cassert>
#include <cmath>

static float f_12tet(u32 note)
{
    i32 offset_from_a4 = note - 69;
    float f_offset = static_cast<float>(offset_from_a4);

    return 440.0 * std::exp2(f_offset / 12.0);
}
