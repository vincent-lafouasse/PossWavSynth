#pragma once

#include <vector>
#include "cool_ints.h"

struct Note
{
    Note(float frequency_, float length_secs_);

    u32 get_n_samples(u32 sample_rate);

    float frequency;
    float length_secs;
};

struct Melody
{
    void add_note(float frequency, float length_secs);
    u32 get_total_n_samples(u32 sample_rate);

    std::vector<Note> notes;
};
