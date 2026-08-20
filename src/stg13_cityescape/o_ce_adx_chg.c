#include "stg13_cityescape/o_ce_adx_chg.h"
#include "sa2b_types.h"
#include "samt/sonic/game.h"
#include "samt/sonic/task.h"
#include "set.h"

extern s32 _rename_GetStageNum(void);
extern void fn_80011DF4(void);
extern void fn_80011FB0(const char *);
extern BOOL fn_8001CC18(s32);
extern s32 fn_8001CD40(void);
extern void _rename_PlayAdxFile(const char *); // some "play track" func
extern s32 _rename_EitherPlayerWithinSphere(NJS_VECTOR *, f32);

// ^ extern
// v in this file
static void ObjectCeAdxChgDest(task *tp);
static void ObjectCeAdxChgExec(task *tp);
static void ObjectCeAdxChgDisp(task *tp);

void ObjectCeAdxChg(task *tp) {
  if (!CheckRangeOut(tp) && _rename_GetStageNum() != STAGE_SHORTCITY_2P) {
    tp->disp = ObjectCeAdxChgDisp;
    tp->exec = ObjectCeAdxChgExec;
    tp->dest = ObjectCeAdxChgDest;
  }
}

void ObjectCeAdxChgDest(task *tp) {
  taskwk *twp = tp->twp;
  if (fn_8001CD40() == 7) {
    twp->mode = 2;
  }
  switch (twp->mode) {
  case 2: {
    _rename_PlayAdxFile("c_escap1.adx"); // Escape From The City
  } break;
  case 1:
  case 3:
  case 4: {
    if (fn_8001CC18(0)) {
      _rename_PlayAdxFile("c_escap1.adx");
    } else {
      // Escape From The City (no bass intro)
      _rename_PlayAdxFile("c_escap3.adx");
    }
  } break;
  case 0:
  default:
    break;
  }
}

void ObjectCeAdxChgExec(task *tp) {
  taskwk *twp = tp->twp;
  if (!CheckRangeOut(tp)) {
    if (_rename_EitherPlayerWithinSphere(&twp->pos, twp->scl.x) &&
        (twp->mode == 0 || twp->mode == 2 || twp->mode == 4)) {
      twp->mode = 1;
      fn_80011DF4();
      fn_80011FB0("c_escap2.adx"); // GUN truck theme
    }
    switch (fn_8001CD40()) {
    case 16: {
      if (twp->mode != 1) {
        _rename_PlayAdxFile("c_escap3.adx");
        twp->mode = 4;
      }
    } break;
    case 13: {
      twp->mode = 2;
    } break;
    case 9: {
      if (twp->mode != 1) {
        twp->mode = 3;
      }
    } break;
    default:
      break;
    }
  }
}

void ObjectCeAdxChgDisp(task *tp) { return; }
