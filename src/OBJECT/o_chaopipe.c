#include "OBJECT/o_chaopipe.h"
#include "samt/ninja/njmatrix.h"
#include "samt/ninja/njtexture.h"
#include "samt/sonic/c_colli.h"
#include "samt/sonic/player.h"
#include "samt/sonic/sound.h"
#include "set.h"
#include "types.h"

extern BOOL _rename_CheckFlag0x20(task *tp);
extern void _rename_SetFlag0x20(task *tp);
extern void fn_800260FC(u32, float, float, float);
extern void fn_8011E158(NJS_CNK_OBJECT *);
extern s32 _rename_GetPlayerCharacter(s32);
extern s32 _rename_EitherPlayerWithinSphere(NJS_VECTOR *, float);
extern void _rename_SetConditionFlag(task *tp, u8 smode);

extern CCL_INFO pipe_colli_info[1];
extern NJS_TEXLIST pipe_tex;
extern NJS_CNK_OBJECT pipe_model;
extern const NJS_POINT3 pipe_src_point;

// ^ extern
// v in this file

static void ObjectChaoPipeDest(task *tp);
static void ObjectChaoPipeExec(task *tp);
static void ObjectChaoPipeDisp(task *tp);

#define GetF1(task) (*(Float *)&task->mwp)
#define GetF2(task) (*(Float *)&task->fwp)

void ObjectChaoPipe(task *tp) {
  taskwk *twp = tp->twp;
  if (!CheckRangeOut(tp)) {
    tp->disp = ObjectChaoPipeDisp;
    tp->exec = ObjectChaoPipeExec;
    tp->dest = ObjectChaoPipeDest;
    twp->smode = 0;
    CCL_Init(tp, pipe_colli_info, ARYLEN(pipe_colli_info), CID_OBJECT);
    GetF1(tp) = 0.0f;
    GetF2(tp) = 0.0f;
  }
}

static void ObjectChaoPipeDest(task *tp) {
  tp->mwp = NULL;
  tp->fwp = NULL;
}

static void ObjectChaoPipeExec(task *tp) {
  taskwk *twp = tp->twp;
  STACK_PAD_VAR(1);
  if (!CheckRangeOut(tp)) {
    if (tp->ocp && !_rename_CheckFlag0x20(tp)) {
      float scalar;
      s32 distance;
      if (_rename_GetPlayerCharacter(0) == PLNO_EGG_WALKER ||
          _rename_GetPlayerCharacter(0) == PLNO_TAILS_WALKER) {
        scalar = 25.0f;
      } else {
        scalar = 13.0f;
      }
      distance = _rename_EitherPlayerWithinSphere(&twp->pos, scalar);
      if (twp->wtimer == 0 && distance != 0 &&
          playertwp[distance - 1]->mode == 42) {
        twp->wtimer = 300;
        GetF1(tp) = 0.0f;
        GetF2(tp) = 0.08f;

      } else if (twp->wtimer != 0) {
        if (twp->wtimer == 270) {
          NJS_POINT3 point;
          njPushMatrixEx();
          njUnitMatrix(NULL);
          njTranslateV(NULL, &twp->pos);
          njRotateZ(NULL, twp->ang.z);
          njRotateX(NULL, twp->ang.x);
          njRotateY(NULL, twp->ang.y);
          njCalcPoint(NULL, &pipe_src_point, &point);
          njPopMatrix(1);
          fn_800260FC((u32)(twp->scl.x) % 3, point.x, point.y, point.z);
          _rename_SetConditionFlag(tp, 1);
          SE_Call(0x100a, NULL, 0, 0);
          _rename_SetFlag0x20(tp);
        }
        twp->wtimer--;
      } else if (distance != 0) {
        playerpwp[distance - 1]->action_sel = 42;
      }
    }
    CCL_Entry(tp);
    GetF1(tp) += GetF2(tp);
    GetF2(tp) = (0.95f * GetF2(tp)) - (0.15f * GetF1(tp));
  }
}

static void ObjectChaoPipeDisp(task *tp) {
  taskwk *twp = tp->twp;
  float scale_x;
  njSetTexture(&pipe_tex);
  njPushMatrix(NULL);
  njTranslateV(NULL, &twp->pos);
  njRotateZ(NULL, twp->ang.z);
  njRotateX(NULL, twp->ang.x);
  njRotateY(NULL, twp->ang.y);
  scale_x = GetF1(tp);
  scale_x = 1.0f - scale_x;
  njScale(NULL, scale_x, 1.0f + (GetF1(tp) * 0.9f), scale_x);
  fn_8011E158(&pipe_model);
  njPopMatrix(1);
}
