#include "melody.h"

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

double up_semitones(double frequency, i16 semitones)
{
    return frequency * exp2((double)semitones / 12.0f);
}

double up_octaves(double frequency, i16 octaves)
{
    return frequency * exp2(octaves);
}

float get_frequency(i16 octave, i16 semitones)
{
    const double up_oct = up_octaves(C0_FREQUENCY, octave);
    const double up_semi = up_semitones(up_oct, semitones);

    return up_semi;
}
