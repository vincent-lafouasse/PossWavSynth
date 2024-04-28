#include "MidiMelody.h"

static bool is_midi_event(const Event* event);
static bool is_meta_event(const Event* event);
static bool is_note_on(const MidiEvent* event);
static bool is_note_off(const MidiEvent* event);

MidiMelody::MidiMelody(const std::list<MTrkEvent>& events, MidiTempo* tempo)
{
    messages.clear();

    u32 current_tick = 0;

    for (const MTrkEvent& mtrk_event : events)
    {
        const Event* event = mtrk_event.getEvent();
        if (is_midi_event(event))
        {
            const MidiEvent* midi_event =
                (const MidiEvent*)mtrk_event.getEvent();
            if (is_note_on(midi_event))
                messages.push_back({NoteOn, midi_event->getNote(),
                                    midi_event->getVelocity(),
                                    current_tick * tempo->tick_len_ms()});
            if (is_note_off(midi_event))
                messages.push_back({NoteOff, midi_event->getNote(),
                                    midi_event->getVelocity(),
                                    current_tick * tempo->tick_len_ms()});
        }
        current_tick += mtrk_event.getDeltaTime().getData();
    }
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
    return (event->getStatus() == MidiType::MidiMessageStatus::NoteOff);
}
