#pragma once

#include "types.h"

namespace Midi {
class Clock {
   public:
    virtual void updateTempo() = 0;
    virtual void updateTimeSignature() = 0;

    virtual ~Clock() = default;
};

class TempoClock final : public Clock {
   public:
    void updateTempo() override {}
    void updateTimeSignature() override {}

    ~TempoClock() = default;
};

class AbsoluteClock final : public Clock {
   public:
    void updateTempo() override {}
    void updateTimeSignature() override {}

    ~AbsoluteClock() = default;
};
}  // namespace Midi
