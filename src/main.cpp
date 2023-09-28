#include <iostream>
#include <vector>

#include "cool_ints.h"
#include "data.h"
#include "melody.h"
#include "oscillator.h"
#include "wav.h"
#include "wavetable.h"

#define SAMPLE_RATE 44100
#define N_CHANNELS 1

#define WAVETABLE_RESOLUTION 1024

// do not use u64
#define SAMPLE_TYPE i32
#define BIT_DEPTH 32
#define SAMPLE_IS_SIGNED true

struct Note
{
    Note(float frequency_, float length_secs_);

    u32 get_n_samples(u32 sample_rate);

    float frequency;
    float length_secs;
};

Note::Note(float frequency_, float length_secs_)
{
    frequency = frequency_;
    length_secs = length_secs_;
}

u32 Note::get_n_samples(u32 sample_rate)
{
    return length_secs * (float)sample_rate;
}

struct Melody
{
    void add_note(float frequency, float length_secs);
    u32 get_total_n_samples(u32 sample_rate);

    std::vector<Note> notes;
};

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

int main()
{
    Melody melody;
    melody.add_note(440.0f, 1.0f);
    melody.add_note(440.0f * 1.5f, 1.0f);

    Wavetable sine_wavetable = Wavetable::get_sine(WAVETABLE_RESOLUTION);
    Oscillator sine_wave = Oscillator::init(&sine_wavetable, SAMPLE_RATE);

    u32 n_samples = melody.get_total_n_samples(SAMPLE_RATE) * N_CHANNELS;

    FloatData float_data(n_samples);

    u32 data_index = 0;

    for (Note note : melody.notes)
    {
        sine_wave.set_frequency(note.frequency);
        u32 note_n_samples = note.get_n_samples(SAMPLE_RATE);
        for (u32 i = 0; i < note_n_samples; i++, data_index++)
        {
            float_data.data[data_index] = sine_wave.get();
            sine_wave.advance();
        }
    }

    Data<SAMPLE_TYPE> data(&float_data, BIT_DEPTH, SAMPLE_IS_SIGNED);

    WavHeader header = WavHeader::init(n_samples * (BIT_DEPTH / 8), N_CHANNELS,
                                       SAMPLE_RATE, BIT_DEPTH);

    WavFile wav_file = WavFile::init("wave.wav", &header, data.data);

    if (wav_file.write())
        std::cout << "success" << std::endl;
    else
        std::cout << "rip" << std::endl;
}
