#include "MidiTempo.h"

#include <iostream>

MidiTempo* MidiTempo::parse(const HeaderChunk& header)
{
    u16 raw_time = header.getDivision();

    bool top_bit = 1 & (raw_time >> 15);
    u16 data = raw_time & 0x7FFF;

    if (top_bit)
        return new FPSMidiTempo(data);
    else
        return new PPQMidiTempo(data);
}

constexpr double default_beat_len_ms = 500000.0; // 120 bpm

PPQMidiTempo::PPQMidiTempo(u16 data) {
    ticks_per_beat = data;
    beat_len_ms = default_beat_len_ms;
};


void PPQMidiTempo::log()
{
    std::cout << "Tempo\t\t" << bpm() << "\n";
    std::cout << "Ticks per beat\t" << ticks_per_beat << "\n";
    std::cout << "Ticks in ms\t" << tick_len_ms() << "\n";
}

FPSMidiTempo::FPSMidiTempo(u16 data) {
    (void)data;
    (void)fps;
    (void)frame_len_ticks;
};

void FPSMidiTempo::log()
{
}
