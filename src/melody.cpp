#include "melody.h"

#include <cmath>

#define C0_FREQUENCY 16.351597831287414

Note::Note(float frequency_, float length_secs_)
{
    frequency = frequency_;
    length_secs = length_secs_;
}

u32 Note::get_n_samples(u32 sample_rate)
{
    return length_secs * (float)sample_rate;
}

void Melody::add_note(float frequency, float length_secs)
{
    notes.push_back(Note(frequency, length_secs));
}

u32 Melody::get_total_n_samples(u32 sample_rate)
{
    u32 n_samples = 0;

    for (size_t i = 0; i < notes.size(); i++)
    {
        n_samples += notes.at(i).get_n_samples(sample_rate);
    }

    return n_samples;
}

double up_semitones(double frequency, double semitones)
{
    return frequency * exp2(semitones / 12.0f);
}

double up_octaves(double frequency, double octaves)
{
    return frequency * exp2(octaves);
}

float get_frequency(float octave, float semitones)
{
    const double up_oct = up_octaves(C0_FREQUENCY, octave);
    const double up_semi = up_semitones(up_oct, semitones);

    return up_semi;
}


Melody soprano()
{
    const float b4 = get_frequency(4, 11);
    const float c5 = get_frequency(5, 0);

    Melody m;
    m.add_note(b4, 1);
    m.add_note(c5, 1);
    return m;
}

Melody bass()
{
    const float g3 = get_frequency(3, 7);
    const float c3 = get_frequency(3, 0);

    Melody m;
    m.add_note(g3, 1);
    m.add_note(c3, 1);
    return m;
}
