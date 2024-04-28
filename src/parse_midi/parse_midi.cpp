#include <cassert>
#include <cstring>

#include "parse_midi.h"

#include "Midi.h"
#include "TrackChunk.h"

float parse_time_division(const HeaderChunk& header)
{
    (void)header;
    return 0;
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
    Midi mid {path};

    const HeaderChunk& header = mid.getHeader();
    assert(strcmp(header.getName(), "MThd") == 0);
    float secs_per_tick = parse_time_division(header);

    const std::list<TrackChunk> tracks = mid.getTracks();
    std::vector<Melody> voices {};

    for (const TrackChunk& track: tracks)
        voices.push_back(track_to_melody(track, secs_per_tick));
    return voices;
}
