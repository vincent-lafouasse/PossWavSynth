#include <cassert>
#include <cstring>
#include <memory>

#include "parse_midi.h"

#include "HeaderChunk.h"
#include "Midi.h"
#include "TrackChunk.h"
#include "MidiTempo.h"

float parse_time_division(const HeaderChunk& header)
{
    (void)header;
    return 0;
}

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

Melody track_to_melody(const TrackChunk& track, float secs_per_tick)
{
    Melody m;
    (void)track;
    (void)secs_per_tick;
    return m;
}

std::vector<Melody> parse_midi(const char* path)
{
    Midi mid{path};

    const HeaderChunk& header = mid.getHeader();

    std::unique_ptr<MidiTempo> tempo(MidiTempo::parse(header));

    const std::list<TrackChunk> tracks = mid.getTracks();
    std::vector<Melody> voices{};

    for (const TrackChunk& track : tracks)
        voices.push_back(track_to_melody(track, 0));
    return voices;
}
