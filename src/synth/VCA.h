#pragma once

#include "utils/cool_ints.h"

enum NoteStatus
{
    On,
    Off
};

class VCA
{
   public:
    VCA() : level(0){};
    VCA(float level) : level(level){};
    float get_amplitude() { return level; };
    void set_level(float level) { this->level = level; }
    void set_level(u32 velocity)
    {
        this->level = static_cast<float>(velocity) / 127;
    }

    float level;
};
