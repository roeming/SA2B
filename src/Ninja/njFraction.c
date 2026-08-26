#include "sa2b_types.h"
#include "samt/ninja/ninja.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/math_api.h"


f32 njFraction2(f32 v, f32 *p);

f32 njFraction(f32 v) {
  static f32 unused = 0;
  return njFraction2(v, &unused);
}

f32 njFraction2(f32 value, f32 *outWholeNumber) {
  switch (fpclassify(value)) {
  case FP_NAN:
  case FP_ZERO: 
    *outWholeNumber = value;
    return value;
  case FP_INFINITE:
    *outWholeNumber = value;
    return 0.0f;
  case FP_SUBNORMAL:
    *outWholeNumber = 0.0f;
    return value;
  // case FP_NORMAL:
  default: {
    int iv = value;
    f32 decimal = value - iv;
    // if no decimal parts, or the mantissa is so big that the exponent jumps are >= 1
    if (*(int *)&decimal == 0 ||
        ((*(int *)&value) & 0x7f800000) >= 0x4b800000) {
      *outWholeNumber = value;
      return 0.0f;
    } else {
      *outWholeNumber = iv;
      return decimal;
    }
  } 
  }
} 
