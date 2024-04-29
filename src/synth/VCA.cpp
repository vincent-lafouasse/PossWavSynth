#include "VCA.h"
#include "midi/MidiMelody.h"

VCA::VCA() = default;

VCA::VCA(float level) : level(level), attack_ticks(100), decay_ticks(100), sustain(1.0), release_ticks(100){};

void VCA::set_adsr(float attack_ms, float decay_ms, float sustain, float release_ms, u32 sample_rate)
{
    attack_ticks = static_cast<u32>(attack_ms * sample_rate / 1000.0);
    decay_ticks = static_cast<u32>(decay_ms * sample_rate / 1000.0);
    release_ticks = static_cast<u32>(release_ms * sample_rate / 1000.0);
    this->sustain = sustain;
}

float interpolate(u32 current, u32 start, u32 end, float target_start, float target_end)
{
    float low_contribution = current - start;
    low_contribution /= (end - start);
    float high_contribution = end - current;
    high_contribution /= (end - start);

    return target_start * low_contribution + target_end * high_contribution;
}


float VCA::get_amplitude(MessageStatus note_status, u32 ticks_since_status_change)
{
    if (note_status == NoteOff)
    {
        if (ticks_since_status_change > release_ticks)
            return 0.0f;
        return interpolate(ticks_since_status_change, 0, release_ticks, sustain, 0.0f) * level;
    }
    
    if (ticks_since_status_change > attack_ticks + decay_ticks)
        return sustain * level;

    if (ticks_since_status_change > attack_ticks)
        return interpolate(ticks_since_status_change - attack_ticks, 0, decay_ticks, 1.0f, sustain) * level;

    return interpolate(ticks_since_status_change, 0, attack_ticks, 0, 1.0f) * level;
}


void VCA::set_level(float level) { this->level = level; }
void VCA::set_level(u32 velocity)
{
    this->level = static_cast<float>(velocity) / 127;
}
