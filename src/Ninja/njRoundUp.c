#include "sa2b_types.h"
#include "math.h"

f32 njRoundUp(f32 v) {
  if (v < 0) {
    return -ceilf(-v);
  }
  return ceilf(v);
}
