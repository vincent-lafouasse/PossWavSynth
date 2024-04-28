#include "parse_midi.h"

#include <cmath>
#include <iostream>

#include "HeaderChunk.h"
#include "MTrkEvent.h"
#include "Midi.h"
#include "MidiTempo.h"
#include "TrackChunk.h"
#include "types.h"

class MelodyConstructor
{
   public:
    MelodyConstructor();
    MelodyConstructor(const std::list<MTrkEvent>& events, MidiTempo* tempo)
        : events(events), tempo(tempo){};

    Melody construct_melody();

    const std::list<MTrkEvent> events;
    MidiTempo* tempo;
};

double midi_note_to_frequency(u16 midi_note)
{
    double offset_from_a4 = midi_note - 69;

    return 440.0 * std::exp2(offset_from_a4 / 12);
}

bool is_midi_event(const Event* event)
{
    return event->getType() == MidiType::EventType::MidiEvent;
}
bool is_meta_event(const Event* event)
{
    return event->getType() == MidiType::EventType::MetaEvent;
}

bool is_note_on(const MidiEvent* event)
{
    return event->getStatus() == MidiType::MidiMessageStatus::NoteOn;
}

bool is_note_off(const MidiEvent* event)
{
    return (event->getStatus() == MidiType::MidiMessageStatus::NoteOff) || (is_note_on(event) && !event->getVelocity());
}

Melody MelodyConstructor::construct_melody()
{
    Melody m;
    u32 current_note = 0;
    u32 current_note_start = 0;

    u32 current_tick = 0;
    double timestamp = 0;

    for (const MTrkEvent& mtrk_event: events)
    {
        const Event* event = mtrk_event.getEvent();
        if (is_midi_event(event))
        {
            const MidiEvent* midi_event = (const MidiEvent*)mtrk_event.getEvent();
            if (is_note_on(midi_event) && current_note == 0)
            {
                current_note = midi_event->getNote();
                current_note_start = current_tick;
            }
        }
        current_tick += mtrk_event.getDeltaTime().getData();
    }

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
