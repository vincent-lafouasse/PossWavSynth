#pragma once

#include "Buffer.hpp"
#include "types.h"

namespace BigEndian {
FourCC readFourCC(Buffer& buf) {
    Byte data[4];

    data[0] = buf.readByte();
    data[1] = buf.readByte();
    data[2] = buf.readByte();
    data[3] = buf.readByte();

    return FourCC(data, 4);
}

u32 readU32(Buffer& buf) {
    u32 byte0 = buf.readByte();
    u32 byte1 = buf.readByte();
    u32 byte2 = buf.readByte();
    u32 byte3 = buf.readByte();

    return byte3 | byte2 << 8 | byte1 << 16 | byte0 << 24;
}

u16 readU16(Buffer& buf) {
    u16 byte0 = buf.readByte();
    u16 byte1 = buf.readByte();

    return byte0 << 8 | byte1;
}
}  // namespace BigEndian
