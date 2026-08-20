#include <math.h>

#define __HI(x) (((s32*)&x)[0])

f32 ceilf(f32 f) {
  int i_f = f;
  f32 diff = f - i_f;
  if (__HI(diff)) {
    if ((__HI(f) & 0x7f800000) >= 0x4b800000) {
      return f;
    } else if (__HI(f) & 0x80000000) {
      return i_f;
    } else {
      return ++i_f;
    }
  }
  return f;
}

f32 floorf(f32 f) {
  int i_f = f;
  f32 diff = i_f - f;
  if (__HI(diff)) {
    if ((__HI(f) & 0x7f800000) >= 0x4b800000) {
      return f;
    } else if (__HI(f) & 0x80000000) {
      return --i_f;
    } else {
      return i_f;
    }
  }
  return f;
}
