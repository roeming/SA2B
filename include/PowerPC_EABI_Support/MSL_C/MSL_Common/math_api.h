#ifndef _MSL_MATH_API_H
#define _MSL_MATH_API_H

#include "types.h"
#include <fdlibm.h>

BEGIN_SCOPE_EXTERN_C

// int __fpclassifyf(f32);
// int __signbitd(f64);
// int __fpclassifyd(f64);

#define FP_SUBNORMAL 5
#define FP_NORMAL 4
#define FP_ZERO 3
#define FP_INFINITE 2
#define FP_NAN 1

static inline int __fpclassifyf(f32 x)
{
	switch ((*(s32*)&x) & 0x7f800000) {
	case 0x7f800000:
	{
		if ((*(s32*)&x) & 0x007fffff)
			return FP_NAN;
		else
			return FP_INFINITE;
		break;
	}
	case 0:
	{
		if ((*(s32*)&x) & 0x007fffff)
			return FP_SUBNORMAL;
		else
			return FP_ZERO;
		break;
	}
	}
	return FP_NORMAL;
}

static inline int __fpclassifyd(f64 x)
{
	switch (__HI(x) & 0x7ff00000) {
	case 0x7ff00000:
	{
		if ((__HI(x) & 0x000fffff) || (__LO(x) & 0xffffffff))
			return FP_NAN;
		else
			return FP_INFINITE;
		break;
	}
	case 0:
	{
		if ((__HI(x) & 0x000fffff) || (__LO(x) & 0xffffffff))
			return FP_SUBNORMAL;
		else
			return FP_ZERO;
		break;
	}
	}
	return FP_NORMAL;
}

#define fpclassify(x) ((sizeof(x) == sizeof(f32)) ? __fpclassifyf((f32)(x)) : __fpclassifyd((f64)(x)))

#define isinf(x)    ((fpclassify(x) == FP_INFINITE))
#define isfinite(x) ((fpclassify(x) > FP_INFINITE))

END_SCOPE_EXTERN_C

#endif
