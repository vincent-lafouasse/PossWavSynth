#include "oscillator.h"

Oscillator Oscillator::init(Wavetable* wavetable, u32 sample_rate)
{
    Oscillator o;

    o.wavetable = wavetable;
    o.sample_rate = sample_rate;
    o.phase = 0.0f;
    o.set_frequency(440.0f);

    return o;
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
    phase -= (phase >= 1.0f);
}
