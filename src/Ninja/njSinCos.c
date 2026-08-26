#include "sa2b_types.h"
#include "samt/ninja/ninja.h"

// pretty sure these were handwritten with asm

f32 njSin(register Angle n) {
#if defined(__MWERKS__)
  register f32 ret;
  // clang-format off
  ASM
  {
    lis r6, njSinCosTbl@ha
    clrlslwi r7, n, 16, 3
    addi r6, r6, njSinCosTbl@l
    add r6, r6, r7
    lfs ret, _njSinCosCache.sinValue(r6)
  }
  // clang-format on
  return ret;
#else
  return njSinCosTbl[(u16)n].sinValue;
#endif
}

f32 njCos(register Angle n) {
#if defined(__MWERKS__)
  register f32 ret;
  // clang-format off
  ASM
  {
    lis r6, njSinCosTbl@ha
    clrlslwi r7, n, 16, 3
    addi r6, r6, njSinCosTbl@l
    add r6, r6, r7
    lfs ret, _njSinCosCache.cosValue(r6)
  }
  // clang-format on
  return ret;
#else
  return njSinCosTbl[(u16)n].cosValue;
#endif
}

void njSinCos(register Angle n, register f32 *sinValue, register f32 *cosValue) {
#if defined(__MWERKS__)
    ASM
    {
        lis r6, njSinCosTbl@ha
        clrlslwi r7, n, 16, 3
        addi r6, r6, njSinCosTbl@l
        add r6, r6, r7
        lfs f0, _njSinCosCache.sinValue(r6)
        lfs f1, _njSinCosCache.cosValue(r6)
        stfs f0, 0x0(sinValue)
        stfs f1, 0x0(cosValue)
    }
#else
  _njSinCosCache *p = &njSinCosTbl[(u16)n];
  *sinValue = p->sinValue;
  *cosValue = p->cosValue;
#endif
}
