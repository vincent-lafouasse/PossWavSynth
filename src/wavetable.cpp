#include "wavetable.h"

#include <cmath>

#define PI 3.141592653589f

static float positive_frac_part(float f);

Wavetable Wavetable::get_square(u32 size)
{
    Wavetable w;
    float sample;

    w.size = size;

    w.data.reserve(size);
    for (u32 i = 0; i < size; i++)
    {
        sample = (i < size / 2) ? 1.0f : -1.0f;
        w.data.push_back(sample);
    }

    return w;
}

Wavetable Wavetable::get_sine(u32 size)
{
    Wavetable w;
    float sample;
    float phase_increment = 2 * PI / (float)size;

    w.size = size;

    w.data.reserve(size);
    for (u32 i = 0; i < size; i++)
    {
        sample = std::sin(phase_increment * (float)i);
        w.data.push_back(sample);
    }

    return w;
}

float Wavetable::at(u32 pos)
{
    pos = pos % size;
    return data.at(pos);
}

float Wavetable::at(float pos)
{
    pos = positive_frac_part(pos);

    float float_index = pos * size;
    u32 lower_index = float_index;
    u32 upper_index = lower_index + 1;

    float lower_contribution = (float_index - lower_index) * at(lower_index);
    float upper_contribution = (upper_index - float_index) * at(upper_index);

    return lower_contribution + upper_contribution;
}

float positive_frac_part(float f)
{
    f = f - (int)f;
    f += (f < 0);
    return f;
}
