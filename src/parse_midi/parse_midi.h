#pragma once

#include <vector>

#include "melody/melody.h"

std::vector<Melody> parse_midi(const char* path);
