#pragma once

#include <list>

#include "MTrkEvent.h"
#include "MidiTempo.h"
#include "utils/cool_ints.h"

enum MessageStatus
{
    NoteOn,
    NoteOff
};

struct Message
{
    MessageStatus status;
    u32 note;
    u32 velocity;
    double timestamp;
};

class MidiMelody
{
   public:
    MidiMelody() = default;
    MidiMelody(const std::list<MTrkEvent>& events, MidiTempo* tempo);

    std::list<Message> messages;
};
