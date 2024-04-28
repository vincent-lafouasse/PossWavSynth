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
const float d3_ref = get_frequency(4, 2);
const float c3 = get_frequency(4, 0);
const float bb2 = get_frequency(3, 10);
const float a2 = get_frequency(3, 9);
const float g2 = get_frequency(3, 7);
const float f2 = get_frequency(3, 5);
const float e2 = get_frequency(3, 4);
const float d2 = get_frequency(3, 2);
const float rest = 0;

enum Direction
{
    Up,
    Down,
};

float transpose(float ref, float multiplier, Direction direction)
{
    if (direction == Down)
        multiplier = 1 / multiplier;
    return ref * multiplier;
}

float maj2(Direction direction)
{
    return transpose(d3_ref, 1.125, direction);
}
float min3(Direction direction)
{
    return transpose(d3_ref, 1.2, direction);
}
float maj3(Direction direction)
{
    return transpose(d3_ref, 1.25, direction);
}
float p4(Direction direction)
{
    return transpose(d3_ref, 4.0 / 3.0, direction);
}
float p5(Direction direction)
{
    return transpose(d3_ref, 1.5, direction);
}

Melody alto_melody()
{
    Melody m;
    m.add_note(d3_ref, 5 * whole);
    return m;
}

Melody soprano_melody()
{
    Melody m;
    m.add_note(d3_ref, whole);
    m.add_note(maj3(Up), half);
    m.add_note(rest, quarter);
    m.add_note(maj2(Up), quarter);
    m.add_note(min3(Up), half);
    m.add_note(p4(Up), half);
    m.add_note(maj3(Up), 2 * whole);
    return m;
}

Melody tenor_melody()
{
    Melody m;
    m.add_note(d3_ref, half);
    m.add_note(maj2(Down), whole);
    m.add_note(rest, quarter);
    m.add_note(maj3(Down), quarter);
    m.add_note(maj3(Down), half);
    m.add_note(maj3(Down), half);
    m.add_note(p4(Down), 2 * whole);
    return m;
}

Melody bass_melody()
{
    Melody m;
    m.add_note(d3_ref, half);
    m.add_note(maj2(Down), half);
    m.add_note(p4(Down), half);
    m.add_note(rest, quarter);
    m.add_note(0.5 * p4(Up), quarter);
    m.add_note(0.5 * min3(Up), half);
    m.add_note(0.5 * maj2(Up), half);
    m.add_note(0.5 * d3_ref, 2 * whole);
    return m;
}
