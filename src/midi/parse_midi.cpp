#include <cassert>
#include <cstring>
#include <memory>

#include "parse_midi.h"

#include "HeaderChunk.h"
#include "Midi.h"
#include "TrackChunk.h"
#include "MidiTempo.h"

Melody track_to_melody(const TrackChunk& track, std::unique_ptr<MidiTempo>& tempo)
{
    Melody m;
    (void)track;
    (void)tempo;
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
        voices.push_back(track_to_melody(track, tempo));
    return voices;
}
