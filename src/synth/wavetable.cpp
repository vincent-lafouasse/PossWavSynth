#include "wavetable.h"

#include <cmath>
#include <fstream>

#define PI 3.141592653589f

constexpr u32 default_wavetable_resolution = 1024;

float Wavetable::at(u32 pos) const
{
    pos = pos % size;
    return data.at(pos);
}

float Wavetable::at(float pos) const
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
        current = std::fabs(data[i]);
        if (std::isgreater(current, max_abs))
            max_abs = current;
    }

    if (max_abs == 0.0f)
        return;

    for (u32 i = 0; i < size; i++)
    {
        data[i] = data[i] / max_abs;
    }
}

namespace Wavetables
{
Wavetable get_empty()
{
    Wavetable w;

    w.size = default_wavetable_resolution;
    w.data.reserve(w.size);

    for (u32 i = 0; i < w.size; i++)
    {
        w.data.push_back(0.0f);
    }

    return w;
}

Wavetable get_saw()
{
    Wavetable w = Wavetables::get_empty();

    float increment = 2.0f / (float)w.size;
    float sample = -1.0f;

    for (u32 i = 0; i < w.size; i++)
    {
        w.data[i] = sample;
        sample += increment;
    }

    return w;
}

Wavetable get_triangle()
{
    Wavetable w = Wavetables::get_empty();

    float sample = -1.0f;
    float increment = 4.0f / (float)w.size;

    for (u32 i = 0; i < w.size; i++)
    {
        if (i == w.size / 2)
        {
            increment *= -1;
        }
        w.data[i] = sample;
        sample += increment;
    }

    return w;
}

Wavetable get_square()
{
    Wavetable w = Wavetables::get_empty();
    float sample;

    for (u32 i = 0; i < w.size; i++)
    {
        sample = (i < w.size / 2) ? 1.0f : -1.0f;
        w.data[i] = sample;
    }

    return w;
}

Wavetable get_sine()
{
    Wavetable w = Wavetables::get_empty();

    float sample;
    float phase_increment = 2 * PI / (float)w.size;

    for (u32 i = 0; i < w.size; i++)
    {
        sample = std::sin(phase_increment * (float)i);
        w.data[i] = sample;
    }

    return w;
}

Wavetable get_harmonic(u32 multiplier)
{
    Wavetable w = Wavetables::get_empty();

    float sample;
    float phase_increment = multiplier * 2 * PI / (float)w.size;

    for (u32 i = 0; i < w.size; i++)
    {
        sample = std::sin(phase_increment * (float)i);
        w.data[i] = sample;
    }

    return w;
}

Wavetable a_cool_additive_wavetable(void)
{
    AdditiveWavetableFactory additive_factory;
    additive_factory.add_harmonic(2, 0.5f);
    additive_factory.add_harmonic(5, 0.25f);

    return additive_factory.get();
}

static float square_fourier_amplitude(u32 n)
{
    if (n % 2 == 0)
        return 0;
    return 1 / static_cast<float>(n);
}

static float triangle_fourier_amplitude(u32 n)
{
    if (n % 2 == 0)
        return 0;

    float one_over_n2 = 1 / static_cast<float>(n * n);

    if (((n - 1) / 2) % 2)
        return one_over_n2;
    else
        return -one_over_n2;
}

Wavetable band_limited_triangle(u32 top_harmonic)
{
    AdditiveWavetableFactory factory;

    for (u32 i = 2; i <= top_harmonic; i++)
        factory.add_harmonic(i, triangle_fourier_amplitude(i));

    return factory.get();
}

Wavetable band_limited_square(u32 top_harmonic)
{
    AdditiveWavetableFactory factory;

    for (u32 i = 2; i <= top_harmonic; i++)
        factory.add_harmonic(i, square_fourier_amplitude(i));

    return factory.get();
}

// static float saw_fourier_amplitude(u32 n);

}  // namespace Wavetables

AdditiveWavetableFactory::AdditiveWavetableFactory()
{
    harmonics.push_back(Harmonic(1, 1.0f));
}

Wavetable AdditiveWavetableFactory::get()
{
    Wavetable w = Wavetables::get_empty();

    for (u32 i = 0; i < harmonics.size(); i++)
    {
        Wavetable harmonic = Wavetables::get_harmonic(harmonics[i].multiplier);

        for (u32 j = 0; j < w.size; j++)
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

Harmonic::Harmonic(float multiplier, float amplitude)
{
    this->multiplier = multiplier;
    this->amplitude = amplitude;
}

void Wavetable::write_to_csv(const std::string& output_filename) const
{
    std::ofstream csv(output_filename);

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
