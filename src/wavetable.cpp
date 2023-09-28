#include "wavetable.h"

#include <cmath>

#define PI 3.141592653589f

Wavetable Wavetable::get_saw(u32 size)
{
    Wavetable w;

    w.size = size;
    w.data.reserve(size);

    float increment = 2.0f / (float)size;
    float sample = -1.0f;

    for (u32 _ = 0; _ < size; _++)
    {
        w.data.push_back(sample);
        sample += increment;
    }

    return w;
}

Wavetable Wavetable::get_triangle(u32 size)
{
    Wavetable w;

    w.size = size;
    w.data.reserve(size);

    float sample = -1.0f;
    float increment = 4.0f / (float)size;

    for (u32 i = 0; i < size; i++)
    {
        if (i == size / 2)
        {
            increment *= -1;
        }
        w.data.push_back(sample);
        sample += increment;
    }

    return w;
}

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

Wavetable Wavetable::get_harmonic(u32 multiplier, u32 size)
{
    Wavetable w;
    float sample;
    float phase_increment = multiplier * 2 * PI / (float)size;

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
    while (std::isgreater(pos, 1.0f))
        pos -= 1.0f;
    while (std::isgreater(0.0f, pos))
        pos += 1.0f;

    float float_index = pos * size;
    u32 lower_index = float_index;
    u32 upper_index = lower_index + 1;

    float lower_contribution = (float_index - lower_index) * at(lower_index);
    float upper_contribution = (upper_index - float_index) * at(upper_index);

    return lower_contribution + upper_contribution;
}
