#pragma once

#include "types.h"

class Buffer {
   public:
    virtual Byte readByte() = 0;
    virtual Byte peekByte() const = 0;
    virtual ~Buffer() {}
};
