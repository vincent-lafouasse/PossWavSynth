#pragma once

#include "HeaderChunk.h"
#include "utils/cool_ints.h"

class MidiTempo
{
   public:
    virtual double get_microsecs_per_tick() = 0;
	static MidiTempo* parse(const HeaderChunk& header);
};

class PPQMidiTempo : public MidiTempo
{
   public:
    PPQMidiTempo(u16 raw_data) {};
	double get_microsecs_per_tick() { return 0; }

   private:
    double bpm;
};
class FPSMidiTempo : public MidiTempo
{
   public:
    FPSMidiTempo(u16 raw_data) {};
	double get_microsecs_per_tick() { return 0; }

   private:
    double fps;
};
