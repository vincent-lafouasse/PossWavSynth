#pragma once

#include "utils/cool_ints.h"

#include "midi/MidiMelody.h"

class VCA
{
   public:
    VCA();
    VCA(float level);
    float get_amplitude(MessageStatus note_status,
                        u32 ticks_since_status_change);
    void set_level(float level);
    void set_level(u32 velocity);
    void set_adsr(float attack_ms,
                  float decay_ms,
                  float sustain,
                  float release_ms,
                  u32 sample_rate);

    float level;
    u32 attack_ticks;
    u32 decay_ticks;
    float sustain;
    u32 release_ticks;
};
