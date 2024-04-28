#include "parse_midi.h"

#include <iostream>
#include <cmath>

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

double midi_note_to_frequency(u16 midi_note)
{
    double offset_from_a4 = midi_note - 69;

    return 440.0 * std::exp2(offset_from_a4 / 12);
}

Melody MelodyConstructor::construct_melody()
{
    Melody m;
    u32 current_note = 0;
    u32 current_tick = 0;
    double timestamp = 0;

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
