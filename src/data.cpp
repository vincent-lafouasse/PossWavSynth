#include "data.h"

#include <cmath>

Signal::Signal(Melody* melody, Oscillator* oscillator)
{
    size = melody->get_total_n_samples(oscillator->sample_rate);
    data = new float[size];

    u32 i = 0;
    u32 note_n_samples;

    for (Note note : melody->notes)
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
