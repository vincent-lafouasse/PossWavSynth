#pragma once

#include <list>
#include <vector>

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
    double timestamp_secs;
    u64 timestamp_quantized;
};

class MidiMelody
{
   public:
    MidiMelody() = default;
    MidiMelody(const std::list<MTrkEvent>& events, MidiTempo* tempo);

    void regularize();
    void quantize(u32 sample_rate);

    std::vector<Message> messages;
};
