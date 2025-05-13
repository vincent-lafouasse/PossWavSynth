#pragma once

#include "Buffer.hpp"
#include "read.h"

#include <cassert>

namespace Midi {
enum class Format : u16 {
    SingleTrack = 0,
    Simultaneous = 1,
    Sequential = 2,
};

class Division {
   public:
    enum class Kind {
        PerQuarter,
        PerFrame,
    };

    virtual ~Division() {}
};

struct Header {
    explicit Header(Buffer& buf) {
        FourCC identifier = BigEndian::readFourCC(buf);
        assert(identifier.as_string() == "MThd");

        u32 size = BigEndian::readU32(buf);
        assert(size == 6);  // header chunk is always 6 bytes

        u16 raw_format = BigEndian::readU16(buf);
        assert(raw_format <= 2);
        this->format = static_cast<Format>(raw_format);

        this->num_tracks = BigEndian::readU16(buf);
        if (this->format == Format::SingleTrack) {
            assert(this->num_tracks == 1);
        }

        this->division = BigEndian::readU16(buf);
    }

    Format format;
    u16 num_tracks;
    u16 division;
};
}  // namespace Midi
