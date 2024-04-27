#pragma once

#include <cstdio>

#include "Signal.h"

class Data
{
public:
   virtual void write(FILE* file) = 0;
   virtual void* get() = 0;

   u32 size;
   u32 sample_rate;
   u32 sample_size_byte;
   u16 bit_depth;
};

class Data32 : public Data
{
public:
   Data32();
   Data32(Signal& signal, u32 sample_rate);
   ~Data32();
   void write(FILE* file);
   void* get();

   i32* data;
};
