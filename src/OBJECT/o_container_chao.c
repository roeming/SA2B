#include "OBJECT/o_container_chao.h"
#include "set.h"
#include "CCL.h"
#include "samt/sonic/njctrl.h"
#include "fabsf.h"
#include "samt/sonic/shadow.h"
#include "samt/sonic/player.h"
#include "OBJECT/ef_crash3D.h"

extern void ds_DrawModelClip(void*);
extern void SE_CallV2_Timer(s32, taskwk*, s32, s32, s32, NJS_VECTOR*);
extern void AddScore(int);

extern void _rename_container_setup(task *tp);
extern void _rename_container_destroy(task *tp);

extern void _rename_CreateChaoKey(NJS_VECTOR *, f32, f32);

extern void fn_13_15F00(task *tp, int, int, CCL_INFO *, int count, int);
extern void fn_13_493A0(NJS_VECTOR *, f32, f32, Angle3 *, f32, f32, f32);
extern void fn_13_496DC(NJS_VECTOR *, f32, f32, f32);
extern void fn_13_15B14(NJS_VECTOR *);
extern BOOL _rename_HasCollectedChaoKey(void);

extern void fn_80025FDC(f32, f32, f32, s32);
extern BOOL fn_8003699C(task *, task *);

extern int lbl_803ADC14;
extern NJS_TEXLIST lbl_13_data_212E8C;

// ^ extern
// v in this file

// bss
static BOOL o_cont_chao_cnkdraw = FALSE;

// data
static NJS_TEXNAME o_cont_chao_texname_0[] = {
    {"sikake_38_128"},
    {"sikake_39_128"},
};

static NJS_TEXLIST o_cont_chao_texlist_0 = {
  o_cont_chao_texname_0,
  ARRAY_COUNT(o_cont_chao_texname_0)
};

static NJS_VECTOR o_cont_chao_vec_0[] = {
#include "assets/o_cont_chao_vec_0.inc"
};

static NJS_VECTOR o_cont_chao_vec_1[] = {
#include "assets/o_cont_chao_vec_1.inc"
};

static NJS_TEX o_cont_chao_uv_0[] = {
#include "assets/o_cont_chao_uv_0.inc"
};

static GJS_ARRAY o_cont_chao_arr_0[] = {
  GJS_ARR_ENTRY(o_cont_chao_vec_0, GJ_VA_POS, GJ_POS_XYZ, GJ_F32),
  GJS_ARR_ENTRY(o_cont_chao_vec_1, GJ_VA_NRM, GJ_NRM_XYZ, GJ_F32),
  GJS_ARR_ENTRY(o_cont_chao_uv_0, GJ_VA_TEX0, GJ_TEX_ST, GJ_S16),
  GJ_VA_NULL,
};

static GJS_MATERIAL o_cont_chao_material_0[] = {
#include "assets/o_cont_chao_material_0.inc"
};

static GJS_MATERIAL o_cont_chao_material_1[] = {
#include "assets/o_cont_chao_material_1.inc"
};

static u8 o_cont_chao_dl_0[] ATTRIBUTE_ALIGN(32) = {
#include "assets/o_cont_chao_dl_0.inc"
};

static u8 o_cont_chao_dl_1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/o_cont_chao_dl_1.inc"
};

static GJS_MESHSET o_cont_chao_meshset_0[] = {
    {
        o_cont_chao_material_0,
        ARRAY_COUNT(o_cont_chao_material_0),
        o_cont_chao_dl_0,
        ARRAY_COUNT(o_cont_chao_dl_0),
    },
    {
        o_cont_chao_material_1,
        ARRAY_COUNT(o_cont_chao_material_1),
        o_cont_chao_dl_1,
        ARRAY_COUNT(o_cont_chao_dl_1),
    },
};

static GJS_MODEL o_cont_chao_mdl_0 = {
    o_cont_chao_arr_0,
    NULL,
    o_cont_chao_meshset_0,
    NULL,
    ARRAY_COUNT(o_cont_chao_meshset_0),
    0,
    {0.f, 10.f - 2e-6, 0.f},
    14.142136f
};

static NJS_TEXNAME o_cont_chao_texname_1[] = {
    {"sikake_38_128"},
    {"sikake_39_128"},
};

static NJS_TEXLIST o_cont_chao_texlist_1 = {
    o_cont_chao_texname_1,
    ARRAY_COUNT(o_cont_chao_texname_1),
};

static s16 o_cont_chao_cnk_mdl_0_tex[] = {
#include "assets/o_cont_chao_cnk_mdl_0_tex.inc"
};

static s32 o_cont_chao_cnk_mdl_0_vtx[] = {
#include "assets/o_cont_chao_cnk_mdl_0_vtx.inc"
};

static NJS_CNK_MODEL o_cont_chao_cnk_mdl_0 = {
    o_cont_chao_cnk_mdl_0_vtx,
    o_cont_chao_cnk_mdl_0_tex,
    {-0.054688f, -1e-6f, 0.0547f},
    10.103906f
};

static NJS_TEXNAME o_cont_chao_texname_2[] = {
    {"sikake_38_128"},
};

static NJS_TEXLIST o_cont_chao_texlist_2 = {
  o_cont_chao_texname_2,
  ARRAY_COUNT(o_cont_chao_texname_2),
};

static s16 o_cont_chao_cnk_mdl_1_tex[] = {
#include "assets/o_cont_chao_cnk_mdl_1_tex.inc"
};

static s32 o_cont_chao_cnk_mdl_1_vtx[] = {
#include "assets/o_cont_chao_cnk_mdl_1_vtx.inc"
};

static NJS_CNK_MODEL o_cont_chao_cnk_mdl_1 = {
    o_cont_chao_cnk_mdl_1_vtx,
    o_cont_chao_cnk_mdl_1_tex,
    {0, -2e-6f, 0},
    10,
};

static NJS_TEXNAME o_cont_chao_texname_3[] = {
    {"sikake_39_128"},
};

static NJS_TEXLIST o_cont_chao_texlist_3 = {
    o_cont_chao_texname_3,
    ARRAY_COUNT(o_cont_chao_texname_3),
};

static s16 o_cont_chao_cnk_mdl_2_tex[] = {
#include "assets/o_cont_chao_cnk_mdl_2_tex.inc"
};

static s32 o_cont_chao_cnk_mdl_2_vtx[] = {
  #include "assets/o_cont_chao_cnk_mdl_2_vtx.inc"
};

static NJS_CNK_MODEL o_cont_chao_cnk_mdl_2 = {
    o_cont_chao_cnk_mdl_2_vtx,
    o_cont_chao_cnk_mdl_2_tex,
    {0, 0, -2e-6f},
    14.142138,
};

NJS_TEXLIST *g_ContChaoTexList[] = {
    &o_cont_chao_texlist_0, &o_cont_chao_texlist_1, &o_cont_chao_texlist_2,
    &o_cont_chao_texlist_3, &lbl_13_data_212E8C, NULL,
};

static ExplosionPiece_t o_cont_chao_explode_pieces[] = {
    {
        &o_cont_chao_texlist_1,
        &o_cont_chao_cnk_mdl_0,
        {0, 10, 10},
        {0, 0, 0},
    },
    {
        &o_cont_chao_texlist_1,
        &o_cont_chao_cnk_mdl_0,
        {8.5, 10, 8.5},
        {0, 0x4000, 0},
    },
    {
        &o_cont_chao_texlist_1,
        &o_cont_chao_cnk_mdl_0,
        {8.5, 10, -8.5},
        {0, 0x8000, 0},
    },
    {
        &o_cont_chao_texlist_2,
        &o_cont_chao_cnk_mdl_1,
        {10, 10, 0},
        {0, 0x4000, 0},
    },
    {
        &o_cont_chao_texlist_1,
        &o_cont_chao_cnk_mdl_0,
        {-8.5, 10, -8.5},
        {0, -0x4000, 0},
    },
    {
        &o_cont_chao_texlist_2,
        &o_cont_chao_cnk_mdl_1,
        {0, 10, -10},
        {0, 0x8000, 0},
    },
    {
        &o_cont_chao_texlist_2,
        &o_cont_chao_cnk_mdl_1,
        {-10, -10, 0},
        {0, -0x4000, 0},
    },
    {
        &o_cont_chao_texlist_1,
        &o_cont_chao_cnk_mdl_0,
        {-8.5, 10, 8.5},
        {0, 0, 0},
    },
    { // lid
        &o_cont_chao_texlist_3,
        &o_cont_chao_cnk_mdl_2,
        {0, 20.05, 0},
        {-0x4000, -0x4000, 0},
    },
};

typedef struct {
  u32 _0;
  NJS_TEXLIST *_4;
  artificial_padding(4, 0xc, NJS_TEXLIST *);
  NJS_MODEL *_C;
} o_cont_chao_dc_draw_t;

static o_cont_chao_dc_draw_t o_cont_chao_dc_draw[3] = {
    {
        1,
        &o_cont_chao_texlist_0,
        {},
        NULL,
    },
    {
        0,
        &o_cont_chao_texlist_1,
        {},
        NULL,
    },
    {
        0,
        &o_cont_chao_texlist_2,
        {},
        NULL,
    },
};

static CCL_INFO o_cont_chao_collision[1] = {
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

static void ContainerChao_disp(task *tp);
static void ContainerChao_dispGC(task *tp);
static void ContainerChao_exec(task *tp);
static void ContainerChao_dest(task *tp);

enum {
    MD_CONTCHAO_0 = 0,
    MD_CONTCHAO_1 = 1,
    MD_CONTCHAO_2 = 2,
};

#define CONT_F1(tp) (*(f32*)&(tp)->awp)

void ContainerChao(task *tp) {
  taskwk *twp = tp->twp;
  if (!CheckRangeOut(tp)) {
    if (o_cont_chao_cnkdraw) {
      tp->disp = ContainerChao_disp;
    } else {
      tp->disp = ContainerChao_dispGC;
    }
    tp->exec = ContainerChao_exec;
    tp->dest = ContainerChao_dest;
    twp->smode = MD_CONTCHAO_0;
    CONT_F1(tp) = -1000000.0f;
    twp->ang.x = 0;
    twp->ang.z = 0;
    CCL_Init(tp, o_cont_chao_collision, ARRAY_COUNT(o_cont_chao_collision), CID_OBJECT);
    twp->scl.y = 0.0f;
    twp->scl.z = 0.0f;
    _rename_container_setup(tp);
  }
}

static void ContainerChao_dest(task *tp) { 
    _rename_container_destroy(tp); 
    tp->awp = NULL;
}

static void ContainerChao_exec(task *tp) {
  taskwk *twp = tp->twp;
  int stackpad;
  if (twp->smode == MD_CONTCHAO_0 && CheckRangeOut(tp)) {
    return;
  }

  if (twp->scl.y > 0.0f) {
    f32 z = twp->scl.z;
    if (twp->scl.y < -z) {
      z = -twp->scl.y;
    }
    twp->pos.y += z;
    twp->scl.y += z;
    twp->scl.z = twp->scl.z * 0.99f - 0.08f;

    if (tp->ctp == NULL) {
      fn_13_15F00(tp, 0, 0, o_cont_chao_collision, ARRAY_COUNT(o_cont_chao_collision),
                  0);
    }

    if (tp->ctp != NULL) {
      taskwk *twp2 = tp->ctp->twp;
      twp2->pos.x = twp->pos.x;
      twp2->pos.z = twp->pos.z;
      twp2->pos.y = twp->pos.y - twp->scl.y;
    }
  } else if (tp->ctp != NULL) {
    FreeTaskC(tp);
  }

  if (twp->scl.y <= 0.0f && twp->scl.z != 0.0f) {
    twp->scl.y = 0.0f;
    twp->scl.z = 0.0f;
    if (fabsf(twp->pos.y - CONT_F1(tp)) < 5.0f) {
      fn_13_493A0(&twp->pos, 10.0f, 10.0f, &twp->ang, 8.0f, 1.2f, 0.5f);
    }
  }

  switch (twp->smode) {
  case MD_CONTCHAO_0:
    if (twp->cwp->flag & 1 && fn_8003699C(tp, twp->cwp->hit_cwp->mytask)) {
      int i;
      NJS_VECTOR sp3C = twp->pos;
      sp3C.y += 10.f;
      SE_CallV2_Timer(0x1011, twp, 1, 0x7f, 0x50, &twp->pos);
      for (i = 0; i < 14; i++) {
        fn_13_496DC(&sp3C, 7.0f + 3.0f * njRandom(), 0.5f + 1.0f * njRandom(),
                    2.5f + 4.0f * njRandom());
      }
      twp->wtimer = 0;
      twp->smode = MD_CONTCHAO_1;
      AddScore(20);
      {
        int player_num = IsThisTaskPlayer(twp->cwp->hit_cwp->mytask);
        if (player_num != -1) {
          SetVelocityP(player_num, 0, 0, 0);
        }
      }
    } else {
      twp->wtimer++;
      if (CONT_F1(tp) == -1000000.0f && (twp->wtimer & 0x1f) == 0) {
        Angle3 sp30;
        sp30.x = 0;
        sp30.y = twp->ang.y;
        sp30.z = 0;
        CONT_F1(tp) =
            GetShadowPos(twp->pos.x, 5.0f + twp->pos.y, twp->pos.z, &sp30);
      }
      if (playerpwp[0]->equipment & 0x2000410) {
        twp->cwp->info->attr |= 0x4000;
      } else {
        twp->cwp->info->attr &= ~0x4000;
      }
      CCL_Entry(tp);
    }
    break;
  case MD_CONTCHAO_1:
    if (twp->wtimer == 1) {
      NJS_VECTOR sp24 = twp->pos;
      fn_13_15B14(&sp24);
    }
    if (twp->wtimer++ > 2) {
      NJS_VECTOR sp18 = twp->pos;
      NJS_VECTOR spC;
      spC.x = 0.0f;
      spC.y = 0.4f;
      spC.z = 0.0f;

      _rename_CreateExplosionEffect(&sp18, twp->ang.y, o_cont_chao_explode_pieces,
                  ARRAY_COUNT(o_cont_chao_explode_pieces), 0.3f, 1.2f,
                  (CONT_F1(tp) != -1000000.0f ? CONT_F1(tp) : twp->pos.y),
                  &spC);

      twp->smode = MD_CONTCHAO_2;
    }
    if (playerpwp[0]->equipment & 0x2000410) {
      twp->cwp->info->attr |= 0x4000;
    } else {
      twp->cwp->info->attr &= ~0x4000;
      CCL_Entry(tp);
    }
    break;
  case MD_CONTCHAO_2:
    if (tp->ocp != NULL && !_rename_CheckFlag0x20(tp) && !CheckBroken(tp)) {
      if (!_rename_HasCollectedChaoKey()) {
        _rename_CreateChaoKey(
            &twp->pos, (CONT_F1(tp) != -1000000.0f ? CONT_F1(tp) : twp->pos.y),
            2.5f);
      } else if (lbl_803ADC14 & 0x100) {
        if ((lbl_803ADC14 & 0x200) == 0) {
          lbl_803ADC14 |= 0x200;
          fn_80025FDC(twp->pos.x, 10.f + twp->pos.y, twp->pos.z, 0);
        }
      } else {
        // v feels like a fake match
        // v has to be defined before i
        // ternary to v doesn't match
        // ternary in function call has regswap
        int v;
        int i;
        lbl_803ADC14 |= 0x100;
        for (i = 0; i < 4; i++) {
          if (i & 1) {
            v = 1;
          } else {
            v = 2;
          }
          fn_80025FDC(twp->pos.x + 10.f * njSin(i * 0x4000),
                      twp->pos.y + 10.f,
                      twp->pos.z + 10.f * njCos(i * 0x4000),
                      v);
        }
      }
    }
    if (tp->ocp != NULL) {
      SetBroken(tp);
      _rename_SetFlag0x20(tp);
      DeadOut(tp);
    } else {
      FreeTask(tp);
    }
    break;
  }
  return;
}

static void ContainerChao_dispGC(task *tp) {
  taskwk *twp = tp->twp;
  njSetTexture(&o_cont_chao_texlist_0);
  njPushMatrix(NULL);
  njTranslateV(NULL, &twp->pos);
  njRotateY(NULL, twp->ang.y);
  OnControl3D(NJD_CONTROL_3D_TRANS_MODIFIER | NJD_CONTROL_3D_SHADOW);
  gjDrawModel(&o_cont_chao_mdl_0);
  OffControl3D(NJD_CONTROL_3D_TRANS_MODIFIER | NJD_CONTROL_3D_SHADOW);
  njPopMatrix(1);
}

static void ContainerChao_disp(task *tp) {
  taskwk *twp = tp->twp;
  njSetTexture(o_cont_chao_dc_draw[0]._4);
  njPushMatrixEx();
  njTranslateEx(&twp->pos);
  njRotateY(NULL, twp->ang.y);
  OnControl3D(NJD_CONTROL_3D_TRANS_MODIFIER | NJD_CONTROL_3D_SHADOW);
  ds_DrawModelClip(o_cont_chao_dc_draw[0]._C);
  OffControl3D(NJD_CONTROL_3D_TRANS_MODIFIER | NJD_CONTROL_3D_SHADOW);
  njPopMatrixEx();
}
