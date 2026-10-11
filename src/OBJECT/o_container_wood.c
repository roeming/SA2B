#include "OBJECT/o_container_wood.h"
#include "set.h"
#include "CCL.h"
#include "samt/sonic/njctrl.h"

extern s32 _rename_GetStageNum(void);

extern void _rename_container_setup(task *tp);
extern void _rename_container_destroy(task *tp);

extern void _rename_njSubVector(NJS_VECTOR *, NJS_VECTOR *, NJS_VECTOR *);
extern void _rename_gjSetTexMtx(NJS_VECTOR *, Angle3 *);
extern void fn_80066820(s32, NJS_VECTOR *, f32);
extern void fn_8006648C(void);

extern int lbl_803ADAD0;
extern NJS_VECTOR *lbl_80175378[];

extern NJS_TEXLIST lbl_13_data_215698;
extern GJS_MODEL lbl_13_data_215A80;
extern CCL_INFO lbl_13_data_216608[1];

// ^ extern
// v in this file

static void ContainerWood_disp(task *tp);
static void ContainerWood_dispSort(task *tp);
static void ContainerWood_exec(task *tp);
static void ContainerWood_dest(task *tp);

enum {
    MD_CONTWOOD_0 = 0,
};

#define CONT_F1(tp) (*(f32*)&(tp)->awp)

void ContainerWood(task *tp) {
  taskwk *twp = tp->twp;
  if (!CheckRangeOut(tp)) {
    tp->disp = ContainerWood_disp;
    tp->exec = ContainerWood_exec;
    tp->dest = ContainerWood_dest;
    switch (_rename_GetStageNum()) {
    case 60:
    case 61:
    case 62:
      tp->disp_sort = ContainerWood_dispSort;
      break;
    }
    twp->smode = MD_CONTWOOD_0;
    CONT_F1(tp) = -1000000.0f;
    twp->scl.y = 0.0f;
    twp->scl.z = 0.0f;
    CCL_InitShare(tp, lbl_13_data_216608, ARRAY_COUNT(lbl_13_data_216608), CID_OBJECT);
    twp->btimer = twp->ang.z;
    _rename_container_setup(tp);
  }
}

static void ContainerWood_dest(task *tp) {
    _rename_container_destroy(tp);
    tp->awp = NULL;
}

static void ContainerWood_disp(task *tp) {
  taskwk *twp = tp->twp;
  NJS_VECTOR v;
  Angle3 ang;
  switch (_rename_GetStageNum()) {
  case 60:
  case 61:
  case 62:
    _rename_njSubVector(&twp->pos, lbl_80175378[lbl_803ADAD0], &v);
    if (njScalor2(&v) < 900.0f) {
      return;
    }
    break;
  }
  njSetTexture(&lbl_13_data_215698);
  njPushMatrixEx();
  njTranslateEx(&twp->pos);
  njRotateY(NULL, twp->ang.y);
  OnControl3D(NJD_CONTROL_3D_TRANS_MODIFIER | NJD_CONTROL_3D_SHADOW);
  ang.x = 0;
  ang.y = twp->ang.y;
  ang.z = 0;
  fn_80066820(0xff, &twp->pos, lbl_13_data_215A80.r);
  _rename_gjSetTexMtx(&twp->pos, &ang);
  gjDrawModel(&lbl_13_data_215A80);
  fn_8006648C();
  OffControl3D(NJD_CONTROL_3D_TRANS_MODIFIER | NJD_CONTROL_3D_SHADOW);
  njPopMatrixEx();
}
