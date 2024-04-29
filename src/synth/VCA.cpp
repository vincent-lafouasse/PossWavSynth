#include "VCA.h"

VCA::VCA() = default;

VCA::VCA(float level) : level(level), attack_ticks(100), decay_ticks(100), sustain(1.0), release_ticks(100){};

void VCA::set_adsr(float attack_ms, float decay_ms, float sustain, float release_ms, u32 sample_rate)
{
    attack_ticks = static_cast<u32>(attack_ms * sample_rate / 1000.0);
    decay_ticks = static_cast<u32>(decay_ms * sample_rate / 1000.0);
    release_ticks = static_cast<u32>(release_ms * sample_rate / 1000.0);
    this->sustain = sustain;
}

float VCA::get_amplitude() { return level; };
void VCA::set_level(float level) { this->level = level; }
void VCA::set_level(u32 velocity)
{
    this->level = static_cast<float>(velocity) / 127;
}
