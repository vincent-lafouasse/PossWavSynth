#include "wavetable.h"

#include <cmath>
#include <fstream>

#define PI 3.141592653589f

AdditiveWavetableFactory::AdditiveWavetableFactory()
{
    harmonics.push_back(Harmonic(1, 1.0f));
}

Wavetable AdditiveWavetableFactory::get(u32 size)
{
    Wavetable w = Wavetable::get_empty(size);

    for (u32 i = 0; i < harmonics.size(); i++)
    {
        Wavetable harmonic =
            Wavetable::get_harmonic(harmonics[i].multiplier, size);

        for (u32 j = 0; j < size; j++)
        {
            w.data[j] += harmonics[i].amplitude * harmonic.data.at(j);
        }
    }

    w.normalize();

    return w;
}

void AdditiveWavetableFactory::add_harmonic(u32 multiplier, float amplitude)
{
    harmonics.push_back(Harmonic(multiplier, amplitude));
}

Harmonic::Harmonic(u32 multiplier_, float amplitude_)
{
    multiplier = multiplier_;
    amplitude = amplitude_;
}

Wavetable Wavetable::get_empty(u32 size)
{
    Wavetable w;

    w.size = size;
    w.data.reserve(size);

    for (u32 i = 0; i < size; i++)
    {
        w.data.push_back(0.0f);
    }

    return w;
}

Wavetable Wavetable::get_saw(u32 size)
{
    Wavetable w = Wavetable::get_empty(size);

    float increment = 2.0f / (float)size;
    float sample = -1.0f;

    for (u32 i = 0; i < size; i++)
    {
        w.data[i] = sample;
        sample += increment;
    }

    return w;
}

Wavetable Wavetable::get_triangle(u32 size)
{
    Wavetable w = Wavetable::get_empty(size);

    float sample = -1.0f;
    float increment = 4.0f / (float)size;

    for (u32 i = 0; i < size; i++)
    {
        if (i == size / 2)
        {
            increment *= -1;
        }
        w.data[i] = sample;
        sample += increment;
    }

    return w;
}

Wavetable Wavetable::get_square(u32 size)
{
    Wavetable w = Wavetable::get_empty(size);
    float sample;

    for (u32 i = 0; i < size; i++)
    {
        sample = (i < size / 2) ? 1.0f : -1.0f;
        w.data[i] = sample;
    }

    return w;
}

Wavetable Wavetable::get_sine(u32 size)
{
    Wavetable w = Wavetable::get_empty(size);

    float sample;
    float phase_increment = 2 * PI / (float)size;

    for (u32 i = 0; i < size; i++)
    {
        sample = std::sin(phase_increment * (float)i);
        w.data[i] = sample;
    }

    return w;
}

Wavetable Wavetable::get_harmonic(u32 multiplier, u32 size)
{
    Wavetable w = Wavetable::get_empty(size);

    float sample;
    float phase_increment = multiplier * 2 * PI / (float)size;

    for (u32 i = 0; i < size; i++)
    {
        sample = std::sin(phase_increment * (float)i);
        w.data[i] = sample;
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

void Wavetable::normalize(void)
{
    float max_abs = 0.0f;
    float current;

    for (u32 i = 0; i < size; i++)
    {
        current = fabs(data[i]);
        if (isgreater(current, max_abs))
            max_abs = current;
    }

    if (max_abs == 0.0f)
        return;

    for (u32 i = 0; i < size; i++)
    {
        data[i] = data[i] / max_abs;
    }
}

void Wavetable::write_to_csv(std::string name)
{
    std::ofstream csv(name);

    for (u32 i = 0; i < size; i++)
    {
        csv << i << ",";
    }
    csv << std::endl;

    for (u32 i = 0; i < size; i++)
    {
        csv << +data[i] << ",";
    }
    csv << std::endl;
    csv.close();
}
