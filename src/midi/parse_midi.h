#pragma once

#include <vector>

#include "MidiMelody.h"

std::vector<MidiMelody> parse_midi(const char* path);
