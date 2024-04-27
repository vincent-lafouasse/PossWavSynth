#include "Signal.h"

#include <cmath>
#include <fstream>
#include <iostream>

Signal::Signal(const Melody& melody, Oscillator* oscillator)
{
    size = melody.get_total_n_samples(oscillator->sample_rate);
    data = new float[size];

    u32 i = 0;
    u32 note_n_samples;

    for (Note note : melody.notes)
    {
        oscillator->set_frequency(note.frequency);
        note_n_samples = note.get_n_samples(oscillator->sample_rate);
        for (u32 _ = 0; _ < note_n_samples; i++, _++)
        {
            data[i] = oscillator->get();
            oscillator->advance();
        }
    }
}

Signal Signal::sum(const Signal& s1, const Signal& s2, float amp1, float amp2)
{
    u32 size = std::max<u32>(s1.size, s2.size);

    Signal s(size);

    for (u32 i = 0; i < s1.size; i++)
        s.data[i] += amp1 * s1.data[i];
    for (u32 i = 0; i < s2.size; i++)
        s.data[i] += amp2 * s2.data[i];
    s.normalize();
    return s;
}

Signal::Signal(u32 size_)
{
    size = size_;
    data = new float[size];

    for (u32 i = 0; i < size; i++)
        data[i] = 0.0f;
}

Signal::~Signal()
{
    delete[] data;
}

void Signal::normalize(void)
{
    float max_abs = 0.0f;
    float current;

    for (u32 i = 0; i < size; i++)
    {
        current = fabs(data[i]);
        if (isgreater(current, max_abs))
            max_abs = current;
    }

    if (max_abs == 0.0f)
        return;

    for (u32 i = 0; i < size; i++)
    {
        data[i] = data[i] / max_abs;
    }
}

void Signal::write_to_csv(void)
{
    std::ofstream csv;
    csv.open("float_data.csv");
    for (u32 i = 0; i < size; i++)
    {
        csv << data[i] << ",";
    }
    csv << std::endl;
    csv.close();
}
