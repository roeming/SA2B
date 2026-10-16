#include "OBJECT/o_container_wood.h"
#include "set.h"
#include "CCL.h"
#include "samt/sonic/njctrl.h"
#include "samt/sonic/game.h"

extern s32 _rename_GetStageNum(void);

extern void _rename_container_setup(task *tp);
extern void _rename_container_destroy(task *tp);

extern void _rename_njSubVector(NJS_VECTOR *, NJS_VECTOR *, NJS_VECTOR *);
extern void _rename_gjSetTexMtx(NJS_VECTOR *, Angle3 *);
extern void fn_80066820(s32, NJS_VECTOR *, f32);
extern void fn_8006648C(void);

extern int lbl_803ADAD0;
extern NJS_VECTOR *lbl_80175378[];

// ^ extern
// v in this file

// bss
static BOOL o_cont_wood_cnkdraw = FALSE;

// data
static NJS_TEXNAME o_cont_wood_texname_0[] = {
    {"sikake_18_128"},
    {"sikake_19_128"},
};

static NJS_TEXLIST o_cont_wood_texlist_0 = {
    o_cont_wood_texname_0,
    ARRAY_COUNT(o_cont_wood_texname_0),
};

static s16 o_cont_wood_cnk_mdl_0_tex[] = {
#include "assets/o_cont_wood_cnk_mdl_0_tex.inc"
};

static s32 o_cont_wood_cnk_mdl_0_vtx[] = {
#include "assets/o_cont_wood_cnk_mdl_0_vtx.inc"
};

static NJS_CNK_MODEL o_cont_wood_cnk_mdl_0 = {
    o_cont_wood_cnk_mdl_0_vtx,
    o_cont_wood_cnk_mdl_0_tex,
    {0.0f, 9.999998f, 0.0f},
    14.142136f,
};

static NJS_VECTOR o_cont_wood_vec_0[] = {
#include "assets/o_cont_wood_vec_0.inc"
};

static NJS_VECTOR o_cont_wood_vec_1[] = {
#include "assets/o_cont_wood_vec_1.inc"
};

static NJS_TEX o_cont_wood_uv_0[] = {
#include "assets/o_cont_wood_uv_0.inc"
};

static GJS_ARRAY o_cont_wood_arr_0[] = {
    GJS_ARR_ENTRY(o_cont_wood_vec_0, GJ_VA_POS, GJ_POS_XYZ, GJ_F32),
    GJS_ARR_ENTRY(o_cont_wood_vec_1, GJ_VA_NRM, GJ_NRM_XYZ, GJ_F32),
    GJS_ARR_ENTRY(o_cont_wood_uv_0, GJ_VA_TEX0, GJ_TEX_ST, GJ_S16),
    GJ_VA_NULL,
};

static GJS_MATERIAL o_cont_wood_material_0[] = {
#include "assets/o_cont_wood_material_0.inc"
};

static GJS_MATERIAL o_cont_wood_material_1[] = {
#include "assets/o_cont_wood_material_1.inc"
};

static u8 o_cont_wood_dl_0[] ATTRIBUTE_ALIGN(32) = {
#include "assets/o_cont_wood_dl_0.inc"
};

static u8 o_cont_wood_dl_1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/o_cont_wood_dl_1.inc"
};

static GJS_MESHSET o_cont_wood_meshset_0[] = {
    {
        o_cont_wood_material_0,
        ARRAY_COUNT(o_cont_wood_material_0),
        o_cont_wood_dl_0,
        ARRAY_COUNT(o_cont_wood_dl_0),
    },
    {
        o_cont_wood_material_1,
        ARRAY_COUNT(o_cont_wood_material_1),
        o_cont_wood_dl_1,
        ARRAY_COUNT(o_cont_wood_dl_1),
    },
};

static GJS_MODEL o_cont_wood_mdl_0 = {
    o_cont_wood_arr_0,
    NULL,
    o_cont_wood_meshset_0,
    NULL,
    ARRAY_COUNT(o_cont_wood_meshset_0),
    0,
    {0.0f, 9.999998f, 0.0f},
    14.142136f,
};

static NJS_TEXNAME o_cont_wood_texname_1[] = {
    {"sikake_18_128"},
};

static NJS_TEXLIST o_cont_wood_texlist_1 = {
    o_cont_wood_texname_1,
    ARRAY_COUNT(o_cont_wood_texname_1),
};

static s16 o_cont_wood_cnk_mdl_1_tex[] = {
#include "assets/o_cont_wood_cnk_mdl_1_tex.inc"
};

static s32 o_cont_wood_cnk_mdl_1_vtx[] = {
#include "assets/o_cont_wood_cnk_mdl_1_vtx.inc"
};

static NJS_CNK_MODEL o_cont_wood_cnk_mdl_1 = {
    o_cont_wood_cnk_mdl_1_vtx,
    o_cont_wood_cnk_mdl_1_tex,
    {0.0f, 0.0f, 0.0f},
    6.818267f,
};

static NJS_TEXNAME o_cont_wood_texname_2[] = {
    {"sikake_18_128"},
};

static NJS_TEXLIST o_cont_wood_texlist_2 = {
    o_cont_wood_texname_2,
    ARRAY_COUNT(o_cont_wood_texname_2),
};

static s16 o_cont_wood_cnk_mdl_2_tex[] = {
#include "assets/o_cont_wood_cnk_mdl_2_tex.inc"
};

static s32 o_cont_wood_cnk_mdl_2_vtx[] = {
#include "assets/o_cont_wood_cnk_mdl_2_vtx.inc"
};

static NJS_CNK_MODEL o_cont_wood_cnk_mdl_2 = {
    o_cont_wood_cnk_mdl_2_vtx,
    o_cont_wood_cnk_mdl_2_tex,
    {0.0f, 0.059847f, 0.0f},
    9.772826f,
};

static NJS_TEXNAME o_cont_wood_texname_3[] = {
    {"sikake_18_128"},
};

static NJS_TEXLIST o_cont_wood_texlist_3 = {
    o_cont_wood_texname_3,
    ARRAY_COUNT(o_cont_wood_texname_3),
};

static s16 o_cont_wood_cnk_mdl_3_tex[] = {
#include "assets/o_cont_wood_cnk_mdl_3_tex.inc"
};

static s32 o_cont_wood_cnk_mdl_3_vtx[] = {
#include "assets/o_cont_wood_cnk_mdl_3_vtx.inc"
};

static NJS_CNK_MODEL o_cont_wood_cnk_mdl_3 = {
    o_cont_wood_cnk_mdl_3_vtx,
    o_cont_wood_cnk_mdl_3_tex,
    {-0.019999f, -0.083719f, -0.074469f},
    9.79003f,
};

NJS_TEXLIST *g_ContWoodTexList[] = {
    &o_cont_wood_texlist_0, &o_cont_wood_texlist_1, &o_cont_wood_texlist_2,
    &o_cont_wood_texlist_3, NULL,
};

// pieces thrown out when the crate breaks: model and how many copies
typedef struct {
    NJS_TEXLIST *texlist;
    NJS_CNK_MODEL *model;
    s32 num;
} o_cont_wood_piece_t;

static o_cont_wood_piece_t o_cont_wood_break_pieces[] = {
    {&o_cont_wood_texlist_1, &o_cont_wood_cnk_mdl_1, 16},
    {&o_cont_wood_texlist_2, &o_cont_wood_cnk_mdl_2, 4},
    {&o_cont_wood_texlist_3, &o_cont_wood_cnk_mdl_3, 4},
};

typedef struct {
    u32 _0;
    NJS_TEXLIST *_4;
    artificial_padding(4, 0xc, NJS_TEXLIST *);
    NJS_MODEL *_C;
} o_cont_wood_dc_draw_t;

static o_cont_wood_dc_draw_t o_cont_wood_dc_draw[4] = {
    {1, &o_cont_wood_texlist_0, {}, NULL},
    {0, &o_cont_wood_texlist_1, {}, NULL},
    {0, &o_cont_wood_texlist_2, {}, NULL},
    {0, &o_cont_wood_texlist_3, {}, NULL},
};

static CCL_INFO o_cont_wood_collision[1] = {
    {
        0,
        CI_FORM_RECTANGLE,
        0x77,
        4,
        0x00004400,
        {0.0f, 10.0f, 0.0f},
        10.0f,
        10.0f,
        10.0f,
        0.0f,
        0,
        0,
        0,
    },
};

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
    case STAGE_B_BIGFOOT:
    case STAGE_B_HOTSHOT:
    case STAGE_B_FDOG:
      tp->disp_sort = ContainerWood_dispSort;
      break;
    }
    twp->smode = MD_CONTWOOD_0;
    CONT_F1(tp) = -1000000.0f;
    twp->scl.y = 0.0f;
    twp->scl.z = 0.0f;
    CCL_InitShare(tp, o_cont_wood_collision, ARRAY_COUNT(o_cont_wood_collision), CID_OBJECT);
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
  case STAGE_B_BIGFOOT:
  case STAGE_B_HOTSHOT:
  case STAGE_B_FDOG:
    _rename_njSubVector(&twp->pos, lbl_80175378[lbl_803ADAD0], &v);
    if (njScalor2(&v) < SQ(30.0f)) {
      return;
    }
    break;
  }
  njSetTexture(&o_cont_wood_texlist_0);
  njPushMatrixEx();
  njTranslateEx(&twp->pos);
  njRotateY(NULL, twp->ang.y);
  OnControl3D(NJD_CONTROL_3D_TRANS_MODIFIER | NJD_CONTROL_3D_SHADOW);
  ang.x = 0;
  ang.y = twp->ang.y;
  ang.z = 0;
  fn_80066820(0xff, &twp->pos, o_cont_wood_mdl_0.r);
  _rename_gjSetTexMtx(&twp->pos, &ang);
  gjDrawModel(&o_cont_wood_mdl_0);
  fn_8006648C();
  OffControl3D(NJD_CONTROL_3D_TRANS_MODIFIER | NJD_CONTROL_3D_SHADOW);
  njPopMatrixEx();
}
