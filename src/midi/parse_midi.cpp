#include "parse_midi.h"

#include <iostream>

#include "HeaderChunk.h"
#include "MTrkEvent.h"
#include "Midi.h"
#include "MidiTempo.h"
#include "TrackChunk.h"

void log_mtrk_event(const MTrkEvent& mtrk_event, u32* tick)
{
    const Event* event = mtrk_event.getEvent();

    std::cout << "event happening at tick " << *tick << std::endl;
    u32 delta_time = mtrk_event.getDeltaTime().getData();
    *tick += delta_time;
}

Melody track_to_melody(const TrackChunk& track, MidiTempo* tempo)
{
    Melody m;

    u32 current_tick = 0;

    for (const MTrkEvent& event: track.getEvents())
        log_mtrk_event(event, &current_tick);

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
        voices.push_back(track_to_melody(track, tempo));
    
    return voices;
}
