#include "melody.h"

#include <cmath>

#define C0_FREQUENCY 16.351597831287414

Note::Note(float frequency_, float length_secs_)
{
    frequency = frequency_;
    length_secs = length_secs_;
}

u32 Note::get_n_samples(u32 sample_rate) const
{
    return length_secs * (float)sample_rate;
}

void Melody::add_note(float frequency, float length_secs)
{
    notes.push_back(Note(frequency, length_secs));
}

u32 Melody::get_total_n_samples(u32 sample_rate) const
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

constexpr float tempo_bpm = 100.f;
constexpr float quarter = (60.0f / tempo_bpm);
constexpr float half = 2 * quarter;
constexpr float whole = 4 * quarter;

const float g3 = get_frequency(4, 7);
const float fs3 = get_frequency(4, 6);
const float f3 = get_frequency(4, 5);
const float e3 = get_frequency(4, 4);
const float d3 = get_frequency(4, 2);
const float c3 = get_frequency(4, 0);
const float bb2 = get_frequency(3, 10);
const float a2 = get_frequency(3, 9);
const float g2 = get_frequency(3, 7);
const float f2 = get_frequency(3, 5);
const float e2 = get_frequency(3, 4);
const float d2 = get_frequency(3, 2);
const float rest = 0;

Melody soprano_melody()
{
    Melody m;
    m.add_note(d3, whole);
    m.add_note(fs3, half);
    m.add_note(rest, quarter);
    m.add_note(e3, quarter);
    m.add_note(f3, half);
    m.add_note(g3, half);
    m.add_note(fs3, whole);
    return m;
}

Melody alto_melody()
{
    Melody m;
    m.add_note(d3, 4 * whole);
    return m;
}

Melody tenor_melody()
{
    Melody m;
    m.add_note(d3, half);
    m.add_note(c3, whole);
    m.add_note(rest, quarter);
    m.add_note(bb2, quarter);
    m.add_note(bb2, half);
    m.add_note(bb2, half);
    m.add_note(a2, whole);
    return m;
}

Melody bass_melody()
{
    Melody m;
    m.add_note(d3, half);
    m.add_note(c3, half);
    m.add_note(a2, half);
    m.add_note(rest, quarter);
    m.add_note(g2, quarter);
    m.add_note(f2, half);
    m.add_note(e2, half);
    m.add_note(d2, whole);
    return m;
}
