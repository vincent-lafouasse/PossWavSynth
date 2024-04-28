#include "parse_midi.h"

#include "HeaderChunk.h"
#include "Midi.h"
#include "MidiTempo.h"
#include "TrackChunk.h"

Melody track_to_melody(const TrackChunk& track, MidiTempo* tempo)
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

    MidiTempo* tempo = MidiTempo::parse(header);
    tempo->log();

    const std::list<TrackChunk> tracks = mid.getTracks();
    std::vector<Melody> voices{};

    for (const TrackChunk& track : tracks)
        voices.push_back(track_to_melody(track, tempo));
    return voices;
}
