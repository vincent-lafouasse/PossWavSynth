#include "MidiTempo.h"

#include <iostream>
#include <stdexcept>

MidiTempo* MidiTempo::parse(const HeaderChunk& header)
{
    u16 raw_time = header.getDivision();

    bool top_bit = 1 & (raw_time >> 15);
    u16 data = raw_time & 0x7FFF;

    bool is_fps = top_bit;
    if (is_fps)
        throw std::invalid_argument("FPS tempo not implemented (yet)");
    // return new FPSMidiTempo(data);

    return new PPQMidiTempo(data);
}

PPQMidiTempo::PPQMidiTempo(u16 data)
{
    constexpr double default_beat_len_ms = 500000.0;  // 120 bpm
    ticks_per_beat = data;
    beat_len_ms = default_beat_len_ms;
};

void PPQMidiTempo::log()
{
    std::cout << "Tempo\t\t" << bpm() << "\n";
    std::cout << "Ticks per beat\t" << ticks_per_beat << "\n";
    std::cout << "Ticks in ms\t" << tick_len_ms() << "\n";
}

#if 0
FPSMidiTempo::FPSMidiTempo(u16 data)
{
    (void)data;
    (void)fps;
    (void)frame_len_ticks;
};

void FPSMidiTempo::log() {}
#endif
