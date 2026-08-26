#include "sa2b_types.h"
#include "math.h"

f32 njRoundOff(f32 v) {
  if (v < 0) {
    return -floorf(-v);
  }
  return floorf(v);
}
