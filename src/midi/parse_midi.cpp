#include "parse_midi.h"

#include <iostream>

#include "HeaderChunk.h"
#include "MTrkEvent.h"
#include "Midi.h"
#include "MidiTempo.h"
#include "TrackChunk.h"

void process_mtrk_event(const MTrkEvent& mtrk_event, u32* tick)
{
    const Event* event = mtrk_event.getEvent();

    std::cout << "event happening at tick " << *tick << std::endl;
    u32 delta_time = mtrk_event.getDeltaTime().getData();
    *tick += delta_time;
}

class MelodyConstructor
{
public:
    MelodyConstructor();
    MelodyConstructor(const std::list<MTrkEvent>& events, MidiTempo* tempo) : events(events), tempo(tempo) {};

    Melody construct_melody();

    const std::list<MTrkEvent> events;
    MidiTempo* tempo;

};

Melody MelodyConstructor::construct_melody()
{
    Melody m;

    return m;
}

std::vector<Melody> parse_midi(const char* path)
{
    Midi mid{path};

    const HeaderChunk& header = mid.getHeader();

    MidiTempo* tempo = MidiTempo::parse(header);
    tempo->log();

    const std::list<TrackChunk> tracks = mid.getTracks();
    u32 n_tracks = tracks.size();
    std::cout << "n tracks " << n_tracks << std::endl;

    std::vector<Melody> voices{};

    for (const TrackChunk& track : tracks)
    {
        MelodyConstructor constructor(track.getEvents(), tempo);
        Melody melody = constructor.construct_melody();
        voices.push_back(melody);
    }

    return voices;
}
