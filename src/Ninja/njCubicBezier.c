#include "sa2b_types.h"
#include "samt/ninja/ninja.h"


void njCubicBezier(float x, NJS_VECTOR *weights, NJS_VECTOR *out) {
  float inv_x = 1.f - x;
  float b0 = inv_x * inv_x * inv_x;
  float b1 = 3.f * inv_x * inv_x * x;
  float b2 = 3.f * inv_x * x * x;
  float b3 = x * x * x;

  out->x = b0 * weights[0].x + b1 * weights[1].x + b2 * weights[2].x +
         b3 * weights[3].x;
  out->y = b0 * weights[0].y + b1 * weights[1].y + b2 * weights[2].y +
         b3 * weights[3].y;
  out->z = b0 * weights[0].z + b1 * weights[1].z + b2 * weights[2].z +
         b3 * weights[3].z;
}
