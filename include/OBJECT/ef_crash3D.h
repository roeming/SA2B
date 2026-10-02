#ifndef __EF_CRASH3D_H_
#define __EF_CRASH3D_H_

#include "sa2b_types.h"
#include "samt/ninja/ninja.h"

typedef struct {
  NJS_TEXLIST * tex;
  NJS_CNK_MODEL* mdl;
  NJS_VECTOR offset;
  NJS_ANGLE3 orientation;
} ExplosionPiece_t;

void _rename_CreateExplosionEffect(NJS_VECTOR *center, Angle yRotation,
                                   ExplosionPiece_t *pieces, int count, f32,
                                   f32, f32, NJS_VECTOR *velocity);

#endif // !__EF_CRASH3D_H_
