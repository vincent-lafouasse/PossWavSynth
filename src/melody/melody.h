#pragma once

#include <vector>
#include "utils/cool_ints.h"

struct Note
{
    Note(float frequency_, float length_secs_);

    u32 get_n_samples(u32 sample_rate) const;

    float frequency;
    float length_secs;
};

struct Melody
{
    void add_note(float frequency, float length_secs);
    u32 get_total_n_samples(u32 sample_rate) const;

    std::vector<Note> notes;
};

float get_frequency(float octave, float semitones);

Melody soprano_melody();
Melody alto_melody();
Melody tenor_melody();
Melody bass_melody();
