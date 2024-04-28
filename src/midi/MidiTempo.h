#pragma once

#include "HeaderChunk.h"
#include "utils/cool_ints.h"

class MidiTempo
{
public:
   virtual double tick_len_ms() = 0;
   static MidiTempo* parse(const HeaderChunk& header);
};

class PPQMidiTempo : public MidiTempo
{
public:
   PPQMidiTempo(u16 data);
   double tick_len_ms() { return beat_len_ms / ticks_per_beat; };
   void set_beat_len_ms(double beat_len_ms) { this->beat_len_ms = beat_len_ms; };

   double bpm() { return 60000000.0 / beat_len_ms; }
   void log();

private:
   u16 ticks_per_beat;
   double beat_len_ms;
};
class FPSMidiTempo : public MidiTempo
{
public:
   FPSMidiTempo(u16 data);
   double tick_len_ms() { return 0; }

private:
   double fps;
   double frame_len_ticks;
};
