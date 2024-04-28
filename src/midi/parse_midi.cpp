#include "parse_midi.h"

#include <cmath>
#include <iostream>

#include "HeaderChunk.h"
#include "MTrkEvent.h"
#include "Midi.h"
#include "MidiTempo.h"
#include "TrackChunk.h"
#include "midi/MidiMelody.h"
#include "types.h"

std::vector<MidiMelody> parse_midi(const char* path)
{
    Midi mid{path};

    const HeaderChunk& header = mid.getHeader();

    MidiTempo* tempo = MidiTempo::parse(header);
    tempo->log();

    const std::list<TrackChunk> tracks = mid.getTracks();
    u32 n_tracks = tracks.size();
    std::cout << "n tracks " << n_tracks << std::endl;

    std::vector<MidiMelody> voices{};

    for (const TrackChunk& track : tracks)
    {
        MidiMelody melody(track.getEvents(), tempo);
        voices.push_back(melody);
    }

    return voices;
}
