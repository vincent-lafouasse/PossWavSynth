#include <cassert>
#include <cstring>

#include "parse_midi.h"

#include "Midi.h"
#include "TrackChunk.h"

class MidiTempo
{
   public:
    virtual double get_microsecs_per_tick() = 0;
};

class PPQMidiTempo : public MidiTempo
{
   private:
    double bpm;
};
class FPSMidiTempo : public MidiTempo
{
   private:
    double fps;
};

float parse_time_division(const HeaderChunk& header)
{
    u16 raw_time = header.getDivision();
    u32 bit_size = 8 * sizeof(raw_time);
    bool top_bit = 1 & (raw_time >> (bit_size - 1));
    u16 data = raw_time & 0x7FFF;
    printf("top bit\t%d\n", top_bit);
    printf("data\t%d\n", data);
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
    Midi mid{path};

    const HeaderChunk& header = mid.getHeader();
    assert(strcmp(header.getName(), "MThd") == 0);

    float secs_per_tick = parse_time_division(header);

    const std::list<TrackChunk> tracks = mid.getTracks();
    std::vector<Melody> voices{};

    for (const TrackChunk& track : tracks)
        voices.push_back(track_to_melody(track, secs_per_tick));
    return voices;
}
