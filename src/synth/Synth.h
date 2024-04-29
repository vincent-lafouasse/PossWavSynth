#pragma once

#include "VCA.h"
#include "oscillator.h"
#include "midi/MidiMelody.h"
#include "DSP/Signal.h"

class Synth
{
public:
    Synth() = default;
    Synth(const Wavetable* wavetable, u32 sample_rate)
    {
        osc = Oscillator(wavetable, sample_rate);
    }
    Signal realize(const MidiMelody& melody);

    Oscillator osc;
    VCA vca;
};
