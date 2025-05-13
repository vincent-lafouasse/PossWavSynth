#pragma once

#include "types.h"

namespace Midi {
struct Event {
   u8 status;
   u8 data0;
   u8 data1;
};
}

// 1011xxxx &
// 10100101
// 1010
