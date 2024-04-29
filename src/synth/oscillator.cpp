#include "oscillator.h"

#include <cmath>

Oscillator::Oscillator(const Wavetable* wavetable, u32 sample_rate)
{
    this->wavetable = wavetable;
    this->sample_rate = sample_rate;

    phase = 0.0f;
    set_frequency(440.0f);
}

void Oscillator::set_frequency(float f)
{
    frequency = f;
    increment = f / sample_rate;
}

float Oscillator::get()
{
    if (frequency == 0.0f)
        return 0.0f;
    return wavetable->at(phase);
}

void Oscillator::advance()
{
    phase += increment;
    while (std::isgreater(phase, 1.0f))
        phase -= 1.0f;
}
