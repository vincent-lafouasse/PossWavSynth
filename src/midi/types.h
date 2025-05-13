#pragma once

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <string>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using Byte = u8;

struct FourCC {
    FourCC() { std::memset(data, 0, 4); }

    FourCC(const Byte* mem, std::size_t n) {
        n = std::min<std::size_t>(n, 4);
        std::memcpy(data, mem, n);
    }

    std::string as_string() const {
        char str[5] = {0};
        std::memcpy(str, data, 4);
        return str;
    }

    Byte data[4];
};
