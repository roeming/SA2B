#include "stg13_cityescape/o_ce_sobj.h"
#include "sa2b_types.h"
#include "samt/ninja/njmatrix.h"
#include "samt/shinobi/sg_maloc.h"
#include "samt/sonic/c_colli.h"
#include "samt/sonic/game.h"
#include "samt/sonic/player.h"
#include "samt/sonic/task.h"
#include "set.h"
#include "fabsf.h"

extern u8 fn_80065388(task *tp);
extern void fn_8006539C(task *tp, u8 smode);
extern NJS_POINT3 lbl_13_data_141294;//  = {60, 30, 130};

// ^ extern
// v in this file
static void ObjectCesobjDest(task *tp);
static void ObjectCesobjExec(task *tp);

#define MWP_00(mwp) (*(ObjectCeSobj_t**)(&(mwp)->spd.x))
#define MWP_04(mwp) (*(s32*)(&(mwp)->spd.y))
#define TWP_08(twp) (*(s32*)(&(twp)->ang.x))

struct ObjectCeSobj_t;

typedef void (*_18_exec_type)(task*, taskwk*, struct ObjectCeSobj_t*);

typedef struct ObjectCeSobj_t{
  /* 0x00 */ s32 _00;
  artificial_padding(0, 0xc, s32);
  /* 0x0C */ CCL_INFO *coll;
  /* 0x10 */ u32 collCount;
  /* 0x14 */ task_exec disp;
  /* 0x18 */ _18_exec_type exec;
  artificial_padding(0x18, 0x28, _18_exec_type);
} ObjectCeSobj_t; // size: 0x28

void ObjectCesobj(task *tp) {
  ObjectCeSobj_t* r29;
  taskwk *twp = tp->twp;
  tp->exec = ObjectCesobjExec;
  tp->dest = ObjectCesobjDest;
  TWP_08(twp) &= 0xFF;

  if (TWP_08(twp) > MWP_04(tp->mwp) - 1) {
    TWP_08(twp) = MWP_04(tp->mwp) - 1;
  }
  
  r29 = &MWP_00(tp->mwp)[TWP_08(twp)];
  if (r29->coll != NULL) {
    CCL_Init(tp, r29->coll, r29->collCount, CID_OBJECT);
  }

  tp->disp = r29->disp;
  tp->work.ptr = NULL;
  if (r29->_00 & 2) {
    tp->work.ptr = syMalloc(sizeof(NJS_MATRIX));
    if (tp->work.ptr) {
      njPushMatrixEx();
      njUnitMatrix(NULL);
      njTranslateEx(&twp->pos);
      njRotateY(NULL, twp->ang.y);
      njGetMatrix(tp->work.ptr);
      njPopMatrixEx();
    }
  }

  if (tp->ocp) {
    twp->smode = fn_80065388(tp);
  }
}

static void ObjectCesobjDest(task *tp) {
  taskwk *twp = tp->twp;
  if (tp->work.ptr) {
    syFree(tp->work.ptr);
    tp->work.ptr = NULL;
  }
  tp->mwp = NULL;
  tp->awp = NULL;
  tp->fwp = NULL;
  if (tp->ocp) {
    fn_8006539C(tp, twp->smode);
  }
}

static void ObjectCesobjExec(task *tp) {
  taskwk *twp = tp->twp;
  if (!CheckRangeOut(tp)) {
    ObjectCeSobj_t *o = &MWP_00(tp->mwp)[TWP_08(twp)];
    if (o->exec != NULL) {
      o->exec(tp, twp, o);
    } else if (twp->cwp != NULL) {
      CCL_Entry(tp);
    }

    twp->mode = 1;
    if (playertwp[0]) {
      NJS_POINT3 xfmed_pos;
      njPushMatrixEx();
      njUnitMatrix(NULL);
      njRotateY(NULL, -twp->ang.y);
      njTranslate(NULL, -twp->pos.x, -twp->pos.y, -twp->pos.z);
      njCalcPoint(NULL, &playertwp[0]->pos, &xfmed_pos);
      njPopMatrixEx();
      if (fabsf(xfmed_pos.x) < lbl_13_data_141294.x &&
          fabsf(xfmed_pos.z) < lbl_13_data_141294.z &&
          fabsf(xfmed_pos.y) < lbl_13_data_141294.y) {
        twp->mode = 0;
      }
    }
  }
}
