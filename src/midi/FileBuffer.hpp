#pragma once

#include <fstream>
#include <vector>

#include "Buffer.hpp"
#include "types.h"

class FileBuffer final : public Buffer {
   public:
    explicit FileBuffer(std::string_view path) : bytes{}, i{0} {
        std::ifstream file(path);

        while (file.good()) {
            bytes.push_back(file.get());
        }
    }

    ~FileBuffer() = default;

    Byte readByte() {
        Byte out = peekByte();
        this->i++;
        return out;
    }

    Byte peekByte() const { return bytes[i]; }

    std::size_t remaining() const { return bytes.size() - i; }
    std::size_t len() const { return bytes.size(); }

   private:
    std::vector<Byte> bytes;
    std::size_t i;
};
