#pragma once

#include "DSP/Signal.h"
#include "oscillator.h"

class Synth
{
   public:
    Synth() = default;
    Synth(const Wavetable* wavetable, u32 sample_rate)
    {
        osc = Oscillator(wavetable, sample_rate);
    }

    Oscillator osc;
};
