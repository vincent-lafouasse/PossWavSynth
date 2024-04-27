#pragma once

#include <cstdio>

#include "Signal.h"

class Data
{
public:
    virtual void write(FILE* file) = 0;
};

class Data32: Data
{
public:
    Data32();
    ~Data32();

    i32* data;
};
