#include "OBJECT/o_ring.h"
#include "CCL.h"
#include "fabsf.h"
#include "samt/sonic/player.h"
#include "samt/sonic/shadow.h"
#include "samt/sonic/sound.h"
#include "set.h"

extern void CalcAdvanceAsPossible(NJS_VECTOR *, NJS_VECTOR *, f32,
                                  NJS_VECTOR *);
extern void *syCalloc(size_t num, size_t size);
extern void _rename_MakeParticle(NJS_VECTOR *, NJS_VECTOR *, f32);
extern void njEnableFog(void);
extern void njDisableFog(void);
extern void gjSetFog(void);
extern void syFree(void *);
extern void SE_CallRing(s8);
extern void AddMechHP(s32, f32);
extern f32 SqMag(f32, f32, f32);
extern s16 GetRingNumber(s32 playerIndex);
extern void AddScore(int);
extern void AddNumRing(int, s16);
extern void _rename_KillPlayer(int);
extern void fn_8006A148_nop(void);

extern NJS_VECTOR lbl_801E5624;
extern BOOL DisableObjectFog;
extern taskwk *lbl_803ADB04;
extern Angle lbl_803AD914;
extern Angle lbl_803AD918;
extern int lbl_803ADAD0;

// ^ extern
// v in this file

typedef struct ringwk {
  /* 0x00 */ NJS_CNK_OBJECT cnkObj;
  /* 0x38 */ NJS_ANGLE3 shadow_ang;
  /* 0x44 */ f32 shadow_posy;
} ringwk; // size: 0x48

#define GET_RING_WK(tp) ((ringwk *)tp->work.ptr)

size_assert(ringwk, 0x48);

typedef struct {
  u8 padding[4];
  /* 0x04 */ f32 _4;
  /* 0x08 */ f32 _8;
  /* 0x04 */ s32 _C;
  /* 0x10 */ s32 flag;
} ringfwk; // size: 0x14

#define GET_RING_FWK(tp) ((ringfwk *)tp->fwp)

typedef struct {
  s32 flag;
  task *tp;
} ringmwk;

#define GET_RING_MWK(tp) ((ringmwk *)tp->mwp)

size_assert(NJS_CNK_OBJECT, 0x38);
size_assert(ringfwk, 0x14);

static NJS_TEXNAME ring_texarray_0[] = {
    {"sikake_05_64"},
};

NJS_TEXLIST _rename_ring_tex_0 = {
    ring_texarray_0,
    ARRAY_COUNT(ring_texarray_0),
};

static s16 ring_s16_poly_list[] = {
#include "assets/ring_s16_poly_list.inc"
};

static s32 ring_s32_vert_list[] = {
#include "assets/ring_s32_vert_list.inc"
};

static NJS_CNK_MODEL ring_model_0 = {
    ring_s32_vert_list,
    ring_s16_poly_list,
    {0.0f, 0.0f, -0.0f},
    3.102889060974121,
};

static NJS_VECTOR ring_vecs_1[] = {
#include "assets/ring_vecs_1.inc"
};

static NJS_VECTOR ring_vecs_2[] = {
#include "assets/ring_vecs_2.inc"
};

static GJS_ARRAY ring_attributes_0[] = {
    {
        GJ_VA_POS,
        sizeof(*ring_vecs_1),
        ARRAY_COUNT(ring_vecs_1),
        GJ_ARR_TYPE(GJ_POS_XYZ, GJ_F32),
        ring_vecs_1,
        sizeof(ring_vecs_1),
    },
    {
        GJ_VA_NRM,
        sizeof(*ring_vecs_2),
        ARRAY_COUNT(ring_vecs_2),
        GJ_ARR_TYPE(GJ_NRM_XYZ, GJ_F32),
        ring_vecs_2,
        sizeof(ring_vecs_2),
    },
    {GJ_VA_NULL},
};

static GJS_MATERIAL ring_material_1[] = {
#include "assets/ring_material_1.inc"
};

static u8 ring_displaylist_1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/ring_displaylist_1.inc"
};

static GJS_MESHSET ring_meshset_0[] = {
    {
        ring_material_1,
        ARRAY_COUNT(ring_material_1),
        ring_displaylist_1,
        ARRAY_COUNT(ring_displaylist_1),
    },
};

static GJS_MODEL model_ring = {
    ring_attributes_0,
    NULL,
    ring_meshset_0,
    NULL,
    ARRAY_COUNT(ring_meshset_0),
    0,
    {0.0f, 0.0f, -0.0f},
    3.102889060974121f,
};

static NJS_VECTOR ring_vecs_5[] = {
#include "assets/ring_vecs_5.inc"
};

static NJS_VECTOR ring_vecs_6[] = {
#include "assets/ring_vecs_6.inc"
};

static GJS_ARRAY ring_attributes_1[] = {
    {
        GJ_VA_POS,
        sizeof(*ring_vecs_5),
        ARRAY_COUNT(ring_vecs_5),
        GJ_ARR_TYPE(GJ_POS_XYZ, GJ_F32),
        ring_vecs_5,
        sizeof(ring_vecs_5),
    },
    {
        GJ_VA_NRM,
        sizeof(*ring_vecs_6),
        ARRAY_COUNT(ring_vecs_6),
        GJ_ARR_TYPE(GJ_NRM_XYZ, GJ_F32),
        ring_vecs_6,
        sizeof(ring_vecs_6),
    },
    {GJ_VA_NULL},
};

static GJS_MATERIAL ring_material_3[] = {
#include "assets/ring_material_3.inc"
};

static u8 ring_displaylist_3[] ATTRIBUTE_ALIGN(32) = {
#include "assets/ring_displaylist_3.inc"
};

static GJS_MESHSET ring_meshset_1[] = {
    {
        ring_material_3,
        ARRAY_COUNT(ring_material_3),
        ring_displaylist_3,
        ARRAY_COUNT(ring_displaylist_3),
    },
};

static GJS_MODEL model_ring_l2 = {ring_attributes_1,
                                  NULL,
                                  ring_meshset_1,
                                  NULL,
                                  ARRAY_COUNT(ring_meshset_1),
                                  0,
                                  {0.f, 0.f, -0.f},
                                  3.119550943374634};

static NJS_VECTOR ring_vecs_3[] = {
#include "assets/ring_vecs_3.inc"
};

static NJS_VECTOR ring_vecs_4[] = {
#include "assets/ring_vecs_4.inc"
};

static GJS_ARRAY ring_attributes_2[] = {
    {
        GJ_VA_POS,
        sizeof(*ring_vecs_3),
        ARRAY_COUNT(ring_vecs_3),
        GJ_ARR_TYPE(GJ_POS_XYZ, GJ_F32),
        ring_vecs_3,
        sizeof(ring_vecs_3),
    },
    {
        GJ_VA_NRM,
        sizeof(*ring_vecs_4),
        ARRAY_COUNT(ring_vecs_4),
        GJ_ARR_TYPE(GJ_NRM_XYZ, GJ_F32),
        ring_vecs_4,
        sizeof(ring_vecs_4),
    },
    {GJ_VA_NULL},
};

static GJS_MATERIAL ring_material_2[] = {
#include "assets/ring_material_2.inc"
};

static u8 ring_displaylist_2[] ATTRIBUTE_ALIGN(32) = {
#include "assets/ring_displaylist_2.inc"
};

static GJS_MESHSET ring_meshset_2[1] = {
    {
        ring_material_2,
        ARRAY_COUNT(ring_material_2),
        ring_displaylist_2,
        ARRAY_COUNT(ring_displaylist_2),
    },
};

static GJS_MODEL model_ring_l1 = {
    ring_attributes_2,
    NULL,
    ring_meshset_2,
    NULL,
    ARRAY_COUNT(ring_meshset_2),
    0,
    {-0.0f, -0.0f, -0.0f},
    3.088042974472046,
};

static NJS_TEXNAME ring_texarray_1[] = {
    {"kyotu32_marukage"},
};

NJS_TEXLIST _rename_ring_tex_1 = {
    ring_texarray_1,
    ARRAY_COUNT(ring_texarray_1),
};

static NJS_VECTOR ring_vecs_7[] = {
#include "assets/ring_vecs_7.inc"
};

static NJS_VECTOR ring_vecs_8[] = {
#include "assets/ring_vecs_8.inc"
};

static NJS_TEX ring_uvs_0[] = {
#include "assets/ring_uvs_0.inc"
};

static GJS_ARRAY ring_attributes_3[] = {
    {
        GJ_VA_POS,
        sizeof(*ring_vecs_7),
        ARRAY_COUNT(ring_vecs_7),
        GJ_ARR_TYPE(GJ_POS_XYZ, GJ_F32),
        ring_vecs_7,
        sizeof(ring_vecs_7),
    },
    {
        GJ_VA_NRM,
        sizeof(*ring_vecs_8),
        ARRAY_COUNT(ring_vecs_8),
        GJ_ARR_TYPE(GJ_NRM_XYZ, GJ_F32),
        ring_vecs_8,
        sizeof(ring_vecs_8),
    },
    {
        GJ_VA_TEX0,
        sizeof(*ring_uvs_0),
        ARRAY_COUNT(ring_uvs_0),
        GJ_ARR_TYPE(GJ_TEX_ST, GJ_S16),
        ring_uvs_0,
        sizeof(ring_uvs_0),
    },
    {GJ_VA_NULL},
};

static GJS_MATERIAL ring_material_4[] = {
#include "assets/ring_material_4.inc"
};

static u8 ring_displaylist_4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/ring_displaylist_4.inc"
};

static GJS_MESHSET ring_meshset_4[] = {
    ring_material_4,
    ARRAY_COUNT(ring_material_4),
    ring_displaylist_4,
    ARRAY_COUNT(ring_displaylist_4),
};

GJS_MODEL _rename_ring_tex_2 = {
    ring_attributes_3,
    NULL,
    NULL,
    ring_meshset_4,
    0,
    ARRAY_COUNT(ring_meshset_4),
    {0, 0, 0},
    7.071067810058594f,
};

static f32 sScaleX = 0.8f;
static f32 sScaleZ = 0.4f;

static CCL_INFO ring_info[] = {
    {
        0,
        CI_FORM_SPHERE,
        0xb0,
        0,
        0x680000,
        {0, 0, 0},
        5.0f,
        0.0f,
        0.0f,
        0.0f,
        0,
        0,
        0,
    },
};

// bss
static s32 colli_timer = 0;
static ringwk *RingObjects = NULL;
static BOOL CleanupRingObjs = FALSE;
static task *RingTP = NULL;

// forward decls

static void RingEnd(task *);
static void CreateRingTask(void);
static void o_ring_10(ringwk *arg);
static ringwk *CreateRingObject(void);
static BOOL o_ring_8(task *tp);
static void o_ring_2(task*);
static void o_ring_1(task* tp, f32 f1);

enum RINGMD {
  RINGMD_0 = 0,
  RINGMD_1 = 1,
  RINGMD_2 = 2,
  RINGMD_3 = 3,
};

static void o_ring_0(task *tp) {
  NJS_VECTOR pos;
  NJS_VECTOR vec;
  int stackPad;
  int increment = 0x4000;
  int i;
  int ang = 0;
  taskwk *twp = tp->twp;
  f32 x = twp->pos.x;
  f32 y = twp->pos.y;
  f32 z = twp->pos.z;

  vec.x = 0.0f;
  vec.y = 0.02f;
  vec.z = 0.0f;
  i = 4;
  while (i > 0) {
    pos.x = x + 4.0f * njSin(ang);
    pos.y = (y + 1.8f * i) - 1.5f;
    pos.z = z + 4.0f * njCos(ang);
    _rename_MakeParticle(&pos, &vec, 2.5f);
    i--;
    ang += increment;
  }
}

void Ring(task *tp) {
  taskwk *twp = tp->twp;
  if (CheckRangeOut(tp)) {
    if (twp->mode != 0) {
      if (tp->mwp) {
        GET_RING_MWK(tp)->flag |= 1;
        GET_RING_MWK(tp)->tp = NULL;
        tp->mwp = NULL;
      }
      tp->mwp = NULL;
    }
    return;
  }

  if (tp->work.ptr) {
    GET_RING_WK(tp)->cnkObj.pos.x = twp->pos.x;
    GET_RING_WK(tp)->cnkObj.pos.y = twp->pos.y;
    GET_RING_WK(tp)->cnkObj.pos.z = twp->pos.z;
    GET_RING_WK(tp)->cnkObj.ang.y = twp->ang.y;
    GET_RING_WK(tp)->shadow_ang = twp->ang;
    GET_RING_WK(tp)->shadow_posy = twp->btimer < 50 && twp->scl.y != -1000000.0f
                                       ? twp->scl.y
                                       : -1000000.0f;
  }

  switch (twp->mode) {
  case RINGMD_0:
  case RINGMD_2:
    if (twp->mode != RINGMD_2) {
      tp->mwp = NULL;
    }
    if (tp->mwp) {
      GET_RING_MWK(tp)->flag &= ~0x1;
      GET_RING_MWK(tp)->tp = tp;
    }
    tp->fwp = syCalloc(1, sizeof(ringfwk));
    CCL_InitShare(tp, ring_info, ARRAY_COUNT(ring_info), 6);
    if (twp->cwp) {
      tp->twp->cwp->flag |= 0x40;
      twp->cwp->colli_range = 5.0;
    }
    if (twp->scl.x == -1.0f) {
      twp->smode = colli_timer;
      colli_timer++;
      if (colli_timer > 8) {
        colli_timer = 0;
      }
    } else {
      twp->smode = -1;
    }
    if ((twp->ang.x & 0xffff) == 1) {
      GET_RING_FWK(tp)->flag |= 1;
      twp->scl.y = -1000000.0f;
    } else {
      twp->scl.y = GetShadowPos(twp->pos.x, twp->pos.y, twp->pos.z, &twp->ang);
    }
    twp->mode = RINGMD_1;

    GET_RING_FWK(tp)->_4 = 0.0f;
    twp->scl.x = -2.0f;
    twp->scl.z = -4.0f;
    twp->id = 17;
    tp->dest = RingEnd;
    tp->work.ptr = CreateRingObject();
    if (tp->work.ptr) {
      GET_RING_WK(tp)->cnkObj.pos.x = twp->pos.x;
      GET_RING_WK(tp)->cnkObj.pos.y = twp->pos.y;
      GET_RING_WK(tp)->cnkObj.pos.z = twp->pos.z;
      GET_RING_WK(tp)->cnkObj.ang.y = twp->ang.y;
      GET_RING_WK(tp)->shadow_ang = twp->ang;
      GET_RING_WK(tp)->shadow_posy = -1000000.0f;
    }
    break;
  case RINGMD_1:
    if (twp->cwp->flag & 1) {
      task *tp2 = CCL_IsHitPlayer(tp);
      if (tp2) {
        BOOL isPlayer;
        twp->mode = RINGMD_3;
        isPlayer = IsThisTaskPlayer(tp2);
        if ((isPlayer == 0 && !(playerpwp[0]->item & 0x4000)) ||
            (isPlayer == 1 && !(playerpwp[1]->item & 0x4000))) {
          AddScore(10);
          AddNumRing(isPlayer, 1);
          AddMechHP(isPlayer, 0.1f);
          SE_CallRing(isPlayer);
        }
        o_ring_0(tp);
      }
    }

    if (!o_ring_8(tp)) {
      CCL_Entry(tp);
      if (GET_RING_FWK(tp)->_C || !lbl_801CC168._37) {
        twp->ang.y += 0x16c;
      }
    } else {
      twp->scl.y = -1000000.0f;
    }

    if (twp->scl.y != -1000000.0f && !(GET_RING_FWK(tp)->flag & 1) &&
        twp->smode >= 0) {
      twp->smode--;
      if (twp->smode == -1) {
        twp->smode = 8;
        if (SqMag(lbl_803ADB04->pos.x - twp->pos.x,
                  lbl_803ADB04->pos.y - twp->pos.y,
                  lbl_803ADB04->pos.z - twp->pos.z) < SQ(400)) {
          f32 f31 = GetShadowPos(twp->pos.x, twp->pos.y, twp->pos.z, &twp->ang);
          f32 f30 = f31 - twp->scl.y;
          if (fabsf(f30) < 8.0f) {
            twp->scl.y = f31;
            twp->pos.y += f30;
          } else {
            task *tobitiriT;
            twp->mode = RINGMD_3;
            tobitiriT = CreateElementalTask(10, 2, &Tobitiri, "Tobitiri");
            if (tobitiriT) {
              taskwk *t2 = tobitiriT->twp;
              t2->pos = twp->pos;
              t2->pos.y -= 10.f;
              t2->ang.y = NJM_DEG_SANG(njRandom() * 360);
            }
          }
        }
      }
    }
    break;
  case RINGMD_3:
    if (tp->mwp) {
      GET_RING_MWK(tp)->flag |= 2;
      GET_RING_MWK(tp)->tp = NULL;
      tp->mwp = NULL;
    }
    if (tp->ocp) {
      DeadOut(tp);
    } else {
      FreeTask(tp);
    }
    break;
  }
}

void o_ring_M1(task *tp) {
  taskwk *twp = tp->twp;
  if (CheckRangeOut(tp)) {
    if (twp->mode != 0) {
      if (tp->mwp) {
        GET_RING_MWK(tp)->flag |= 1;
        GET_RING_MWK(tp)->tp = NULL;
        tp->mwp = NULL;
      }
      tp->mwp = NULL;
    }
    return;
  }

  switch (twp->mode) {
  case RINGMD_0:
  case RINGMD_2:
    if (twp->mode != RINGMD_2) {
      tp->mwp = NULL;
    }
    if (tp->mwp) {
      GET_RING_MWK(tp)->flag &= ~0x1;
      GET_RING_MWK(tp)->tp = tp;
    }
    tp->fwp = syCalloc(1, sizeof(ringfwk));
    
    if (twp->scl.x == -1.0f) {
      twp->smode = colli_timer;
      colli_timer++;
      if (colli_timer > 8) {
        colli_timer = 0;
      }
    } else {
      twp->smode = -1;
    }
    twp->scl.y = GetShadowPos(twp->pos.x, twp->pos.y, twp->pos.z, &twp->ang);
    twp->mode = RINGMD_1;

    GET_RING_FWK(tp)->_4 = 0.0f;
    twp->scl.x = -2.0f;
    twp->scl.z = -4.0f;
    twp->id = 17;
    tp->dest = RingEnd;
    tp->disp = o_ring_2;
    break;
  case 1: {
    int i;
    int isPlayer = -1;
    for (i = 0; i < 2 && playertwp[i] != NULL && playertwp[i]->cwp != NULL;
         i++) {
      if (lbl_801CC168._38 & (1 << i) &&
          njDistanceP2P(&playertwp[i]->cwp->info->center, &twp->pos) < 14.0f) {
        isPlayer = i;
        break;
      }
    }
    if (isPlayer >= 0) {
      twp->mode = RINGMD_3;
      if ((isPlayer == 0 && !(playerpwp[0]->item & 0x4000)) ||
          (isPlayer == 1 && !(playerpwp[1]->item & 0x4000))) {
        AddScore(10);
        AddNumRing(isPlayer, 1);
        AddMechHP(isPlayer, 0.1f);
        SE_CallRing(isPlayer);
      }
      o_ring_0(tp);
    }
    if (!o_ring_8(tp)) {
      // CCL_Entry(tp);
      if (GET_RING_FWK(tp)->_C || !lbl_801CC168._37) {
        twp->ang.y += 0x16c;
      }
    } else {
      twp->scl.y = -1000000.0f;
    }

    if (twp->scl.y != -1000000.0f && twp->smode >= 0) {
      twp->smode--;
      if (twp->smode == -1) {
        twp->smode = 8;
        if (SqMag(lbl_803ADB04->pos.x - twp->pos.x,
                  lbl_803ADB04->pos.y - twp->pos.y,
                  lbl_803ADB04->pos.z - twp->pos.z) < SQ(400)) {
          f32 f31 = GetShadowPos(twp->pos.x, twp->pos.y, twp->pos.z, &twp->ang);
          f32 f30 = f31 - twp->scl.y;
          if (fabsf(f30) < 8.0f) {
            twp->scl.y = f31;
            twp->pos.y += f30;
          } else {
            task *tobitiriT;
            twp->mode = RINGMD_3;
            tobitiriT = CreateElementalTask(10, 2, &Tobitiri, "Tobitiri");
            if (tobitiriT) {
              taskwk *t2 = tobitiriT->twp;
              t2->pos = twp->pos;
              t2->pos.y -= 10.f;
              t2->ang.y = NJM_DEG_SANG(njRandom() * 360);
            }
          }
        }
      }
    }
  } break;
  case 3:
    if (tp->mwp) {
      GET_RING_MWK(tp)->flag |= 2;
      GET_RING_MWK(tp)->tp = NULL;
      tp->mwp = NULL;
    }
    if (tp->ocp) {
      DeadOut(tp);
    } else {
      FreeTask(tp);
    }
    break;
  }
}

static void o_ring_1(task* tp, f32 f1) {
  taskwk* twp = tp->twp;
  njSetTexture(&_rename_ring_tex_1);
  njPushMatrixEx();
  njTranslate(NULL, twp->pos.x, f1 + 0.2f, twp->pos.z);
  njRotateZ(NULL, twp->ang.z);
  njRotateX(NULL, twp->ang.x);
  njRotateY(NULL, twp->ang.y);
  njScale(NULL, sScaleX, 1.0f, sScaleZ);
  gjDrawModel(&_rename_ring_tex_2);
  njPopMatrixEx();
}

static void o_ring_2(task *tp) {
  taskwk *twp = tp->twp;
  if (lbl_801CC168._38 & (1 << lbl_803ADAD0) || lbl_801CC168._9) {
    if (twp->btimer < 50 && twp->scl.y != -1000000.0f) {
      o_ring_1(tp, twp->scl.y);
    }
    if (DisableObjectFog) {
      njDisableFog();
      gjSetFog();
    }
    njSetTexture(&_rename_ring_tex_0);
    njPushMatrixEx();
    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);
    njCnkCacheDrawModel(&ring_model_0);
    njPopMatrixEx();
    if (DisableObjectFog) {
      njEnableFog();
      gjSetFog();
    }
  }
}

void o_ring_3() {
  njSetTexture(&_rename_ring_tex_0);
  if (DisableObjectFog) {
    njDisableFog();
    gjSetFog();
  }
  njCnkCacheDrawModel(&ring_model_0);
  if (DisableObjectFog) {
    njEnableFog();
    gjSetFog();
  }
}

void DamegeRingScatter(s32 playerIndex) {
  f32 f31 = njRandom() * 360.0f;
  int ringNum = GetRingNumber(playerIndex);
  int i;
  if (ringNum > 20) {
    ringNum = 20;
  } else if (ringNum == 0) {
    if (playerpwp[playerIndex]->basechar != PLNO_EGG_WALKER &&
        playerpwp[playerIndex]->basechar != PLNO_TAILS_WALKER) {
      _rename_KillPlayer(playerIndex);
      fn_8006A148_nop();
    }
    return;
  }
  AddNumRing(playerIndex, -GetRingNumber(playerIndex));
  for (i = 0; i < ringNum; i++) {
    task *tp = CreateFundamentalTask(10, 2, Tobitiri);
    if (tp) {
      taskwk *twk = tp->twp;
      twk->pos = playertwp[playerIndex]->pos;
      twk->ang.y = NJM_DEG_ANG(f31 + (360 * i / ringNum));
    }
  }
  SE_Call(0x8014, NULL, 0, 0);
}

static int o_ring_5(NJS_VECTOR *p) {
  int out = 0;
  if (p->x > 0.9f) {
    out = 1;
  }
  if (p->x < -0.9f) {
    out = 0;
  }
  if (p->y > 0.9f) {
    out = 3;
  }
  if (p->y < -0.9f) {
    out = 2;
  }
  if (p->z > 0.9f) {
    out = 5;
  }
  if (p->z < -0.9f) {
    out = 4;
  }
  return out;
}

void Tobitiri(task *tp) {
  taskwk *twp = tp->twp;
  anywk *awp = tp->awp;
  f32 f31, f30, f29;
  task *t;
  if (CheckRangeOut(tp)) {
    return;
  }
  if (GET_RING_WK(tp) != NULL) {
    GET_RING_WK(tp)->cnkObj.pos.x = twp->pos.x;
    GET_RING_WK(tp)->cnkObj.pos.y = twp->pos.y;
    GET_RING_WK(tp)->cnkObj.pos.z = twp->pos.z;

    GET_RING_WK(tp)->cnkObj.ang.y = NJM_DEG_SANG(GET_RING_FWK(tp)->_4);
    GET_RING_WK(tp)->shadow_ang.x = twp->ang.x;

    GET_RING_WK(tp)->shadow_ang.y = NJM_DEG_SANG(GET_RING_FWK(tp)->_4);
    GET_RING_WK(tp)->shadow_ang.z = twp->ang.z;

    if (twp->mode != RINGMD_1) {
      GET_RING_WK(tp)->shadow_posy = GET_RING_FWK(tp)->_8 + 0.4f;
      // flicker 2 frames on, 2 frames off
      if (twp->wtimer & 2) {
        GET_RING_WK(tp)->cnkObj.evalflags &= ~NJD_EVAL_HIDE;
      } else {
        GET_RING_WK(tp)->cnkObj.evalflags |= NJD_EVAL_HIDE;
      }
    } else {
      GET_RING_WK(tp)->shadow_posy = awp->work.f[0] + 0.4f;
      if (GET_RING_FWK(tp)->_C == 0 && lbl_801CC168._37) {
        if (twp->smode > 46) {
          GET_RING_WK(tp)->cnkObj.evalflags &= ~NJD_EVAL_HIDE;
        } else {
          GET_RING_WK(tp)->cnkObj.evalflags |= NJD_EVAL_HIDE;
        }
      }
    }
  }

  switch (twp->mode) {
  case 0:
    tp->fwp = syCalloc(1, sizeof(ringfwk));
    if (tp->fwp == NULL) {
      return;
    }
    GET_RING_FWK(tp)->_C = lbl_801CC168._37;
    switch (o_ring_5(&lbl_801E5624)) {
    case 1:
      awp->work.f[0] = twp->pos.x + 100.0f;
      break;
    case 0:
      awp->work.f[0] = twp->pos.x - 100.0f;
      break;
    case 3:
      awp->work.f[0] = twp->pos.y + 100.0f;
      break;
    default:
    case 2:
      awp->work.f[0] = twp->pos.y - 100.0f;
      break;
    case 5:
      awp->work.f[0] = twp->pos.z + 100.0f;
      break;
    case 4:
      awp->work.f[0] = twp->pos.z - 100.0f;
      break;
    }
    awp->work.f[1] = colli_timer;
    colli_timer++;
    if (colli_timer > 8) {
      colli_timer = 0;
    }
    CCL_InitShare(tp, ring_info, ARRAY_COUNT(ring_info), 7);
    if (twp->cwp) {
      twp->cwp->colli_range = 5.0f;
    }
    twp->mode = 1;
    twp->pos.x -= lbl_801E5624.x * 10.0f;
    twp->pos.y -= lbl_801E5624.y * 10.0f;
    twp->pos.z -= lbl_801E5624.z * 10.0f;
    {
      NJS_VECTOR sp10C;
      sp10C.y = 1.8f;
      sp10C.x = 0.4f * njSin(twp->ang.y);
      sp10C.z = 0.4f * njCos(twp->ang.y);
      njPushMatrixEx();
      njUnitMatrix(NULL);
      njRotateZ(NULL, lbl_803AD914);
      njRotateX(NULL, lbl_803AD918);
      njCalcVector(NULL, &sp10C, &twp->scl);
      njPopMatrixEx();
    }
    GET_RING_FWK(tp)->_4 = (f32)(int)NJM_DEG_SANG(njRandom() * 360);
    twp->cwp->flag &= ~0x40;
    tp->dest = RingEnd;
    tp->work.ptr = CreateRingObject();
    if (tp->work.ptr != NULL) {
      GET_RING_WK(tp)->cnkObj.pos.x = twp->pos.x;
      GET_RING_WK(tp)->cnkObj.pos.y = twp->pos.y;
      GET_RING_WK(tp)->cnkObj.pos.z = twp->pos.z;

      GET_RING_WK(tp)->cnkObj.ang.y = NJM_DEG_SANG(GET_RING_FWK(tp)->_4);

      GET_RING_WK(tp)->shadow_ang.x = 0;
      GET_RING_WK(tp)->shadow_ang.y = NJM_DEG_SANG(GET_RING_FWK(tp)->_4);
      GET_RING_WK(tp)->shadow_ang.z = 0;

      GET_RING_WK(tp)->shadow_posy = twp->pos.y + 3.44f;
    }
    break;
  case 1:
    if (GET_RING_FWK(tp)->_C || !lbl_801CC168._37) {
      GET_RING_FWK(tp)->_4 += 5.0f;
    }
    if (twp->cwp->flag & 1 && (t = CCL_IsHitPlayer(tp))) {
      twp->cwp->flag &= ~1;
      GET_RING_FWK(tp)->_4 = 0.0f;
      twp->scl.x = -2.0f;
      twp->scl.z = -4.0f;
      twp->pos.y += 3.44f;
      twp->mode = 4;
      {
        int playerIndex = IsThisTaskPlayer(t);
        if ((playerIndex == 0 && !(playerpwp[0]->item & 0x4000)) ||
            (playerIndex == 1 && !(playerpwp[1]->item & 0x4000))) {
          AddNumRing(playerIndex, 1);
          SE_CallRing(playerIndex);
          AddMechHP(playerIndex, 0.1f);
        }
      }
    } else {
      awp->work.f[1] -= 1.0f;
      if (awp->work.f[1] < 0.0f) {
        int r29 = o_ring_5(&lbl_801E5624);
        xyyzzxsdwstr sp3c;
        u8 stackpad[0xc];
        sp3c.pos = twp->pos;
        sp3c.pos.x -= 3.44f * lbl_801E5624.x;
        sp3c.pos.y -= 3.44f * lbl_801E5624.y;
        sp3c.pos.z -= 3.44f * lbl_801E5624.z;
        GetShadowPosXYZ(&sp3c);
        if (sp3c.hit[r29].findflag) {
          awp->work.f[0] = sp3c.hit[r29].onpos;
          twp->ang.x = sp3c.hit[r29].angx;
          twp->ang.z = sp3c.hit[r29].angz;
        } else {
          switch (r29) {
          case 1:
            awp->work.f[0] = twp->pos.x + 100.0f;
            break;
          case 0:
            awp->work.f[0] = twp->pos.x - 100.0f;
            break;
          case 3:
            awp->work.f[0] = twp->pos.y + 100.0f;
            break;
          default:
          case 2:
            awp->work.f[0] = twp->pos.y - 100.0f;
            break;
          case 5:
            awp->work.f[0] = twp->pos.z + 100.0f;
            break;
          case 4:
            awp->work.f[0] = twp->pos.z - 100.0f;
            break;
          }
        }
        awp->work.f[1] = 8.f;
      }

      if (GET_RING_FWK(tp)->_C || !lbl_801CC168._37) {
        int r29;
        NJS_POINT3 sp24;
        u8 stackpad[0xc];
        NJS_VECTOR spC;
        twp->wtimer++;
        if (twp->wtimer > 240) {
          twp->mode = 2;
          GET_RING_FWK(tp)->_8 = awp->work.f[0];
          twp->scl.x = 0;
          twp->scl.z = 0;
          twp->wtimer = 0;
          return;
        }

        r29 = o_ring_5(&lbl_801E5624);
        switch (r29) {
        case 0:
        case 1:
          f31 = awp->work.f[0];
          f30 = twp->pos.y;
          f29 = twp->pos.z;
          break;
        default:
          f31 = twp->pos.x;
          f30 = awp->work.f[0];
          f29 = twp->pos.z;
          break;
        case 4:
        case 5:
          f31 = twp->pos.x;
          f30 = twp->pos.y;
          f29 = awp->work.f[0];
          break;
        }
        twp->scl.y -= -0.08f * lbl_801E5624.y;
        if (twp->scl.y < -4.0f) {
          twp->scl.y = -4.0f;
        }
        if (twp->scl.y > 4.0f) {
          twp->scl.y = 4.0f;
        }
        twp->pos.y += twp->scl.y;

        twp->scl.x -= -0.08f * lbl_801E5624.x;
        if (twp->scl.x < -4.0f) {
          twp->scl.x = -4.0f;
        }
        if (twp->scl.x > 4.0f) {
          twp->scl.x = 4.0f;
        }
        twp->pos.x += twp->scl.x;

        twp->scl.z -= -0.08f * lbl_801E5624.z;
        if (twp->scl.z < -4.0f) {
          twp->scl.z = -4.0f;
        }
        if (twp->scl.z > 4.0f) {
          twp->scl.z = 4.0f;
        }
        twp->pos.z += twp->scl.z;

        twp->scl.x *= 1 - (1.f / 200);
        twp->scl.y *= 1 - (1.f / 200);
        twp->scl.z *= 1 - (1.f / 200);
        njPushMatrixEx();
        njUnitMatrix(NULL);
        njRotateX(NULL, -twp->ang.x);
        njRotateZ(NULL, -twp->ang.z);
        njTranslate(NULL, -f31, -f30, -f29);
        njCalcPoint(NULL, &twp->pos, &sp24);
        njCalcVector(NULL, &twp->scl, &spC);
        if (sp24.y < 3.44f) {
          sp24.y = 3.44f;
          spC.y = fabsf(spC.y) * 0.4f;
          spC.x *= 1 - (1.f / 20);
          spC.z *= 1 - (1.f / 20);
          r29 = -1;
        }
        if (r29 == -1) {
          njUnitMatrix(NULL);
          njTranslate(NULL, f31, f30, f29);
          njRotateZ(NULL, twp->ang.z);
          njRotateX(NULL, twp->ang.x);
          njCalcPoint(NULL, &sp24, &twp->pos);
          njCalcVector(NULL, &spC, &twp->scl);
        }
        njPopMatrixEx();
      }
      if (GET_RING_FWK(tp)->_C || !lbl_801CC168._37) {
        twp->smode++;
      }
      if (twp->smode > 46) {
        f32 oldv;
        twp->smode = 47;
        oldv = twp->pos.y;
        twp->pos.y += 3.44f;
        CCL_Entry(tp);
        twp->pos.y = oldv;
      }
    }
    break;

  case 2:
    if (GET_RING_FWK(tp)->_C || !lbl_801CC168._37) {
      GET_RING_FWK(tp)->_4 += 5.0f;
    }
    if (twp->cwp->flag & 1 && (t = CCL_IsHitPlayer(tp))) {
      int playerIndex;
      twp->cwp->flag &= ~1;
      twp->mode = 4;
      GET_RING_FWK(tp)->_4 = 0.0f;
      twp->scl.x = -2.0f;
      twp->scl.z = -4.0f;
      playerIndex = IsThisTaskPlayer(t);
      if ((playerIndex == 0 && !(playerpwp[0]->item & 0x4000)) ||
          (playerIndex == 1 && !(playerpwp[1]->item & 0x4000))) {
        AddNumRing(playerIndex, 1);
        SE_CallRing(playerIndex);
        AddMechHP(playerIndex, 0.1f);
      }
    } else {
      f32 f29 = twp->pos.y;
      f32 f30 = twp->pos.x;
      f32 f31 = twp->pos.z;
      twp->pos.y += 3.44f;
      twp->pos.x += twp->scl.x;
      twp->pos.z += twp->scl.z;
      CCL_Entry(tp);
      twp->pos.y = f29;
      twp->pos.x = f30;
      twp->pos.z = f31;
      if (GET_RING_FWK(tp)->_C || !lbl_801CC168._37) {
        twp->wtimer++;
        if (twp->wtimer >= 180) {
          twp->mode = 3;
        }
      }
    }
    break;

  case 4:
    o_ring_0(tp);
    // fallthrough
  case 3:
    DestroyTask(tp);
    return;
  }
}

static void RingEnd(task *tp) {
  if (tp->work.ptr) {
    o_ring_10(GET_RING_WK(tp));
  }
  if (tp->mwp) {
    GET_RING_MWK(tp)->flag &= ~1;
    GET_RING_MWK(tp)->tp = NULL;
    tp->mwp = NULL;
  }
  syFree(tp->fwp);
  tp->fwp = NULL;
  tp->mwp = NULL;
}

static BOOL o_ring_8(task *tp) {
  playerwk *pwp;
  taskwk *twp = tp->twp;
  taskwk *twp2;
  int i = 0;
  int r7 = 0;
  int r0;
  f32 d;
  u8 stackpad[0x10];

  for (i; i < 2; i++) {
    if (playerpwp[i] != NULL && playerpwp[i]->item & 2) {
      r7 |= 1 << i;
    }
  }

  if (r7 == 0) {
    return FALSE;
  }

  if (r7 == 3) {
    f32 p1 = njDistanceP2P(&twp->pos, &playertwp[0]->pos);
    f32 p2 = njDistanceP2P(&twp->pos, &playertwp[1]->pos);
    if (p1 < p2) {
      r0 = 0;
    } else if (p1 > p2) {
      r0 = 1;
    } else {
      return FALSE;
    }
  } else if (r7 == 1) {
    r0 = 0;
  } else if (r7 == 2) {
    r0 = 1;
  } else {
    return FALSE;
  }

  pwp = playerpwp[r0];
  d = njDistanceP2P(&twp->pos, &playertwp[r0]->pos);
  if (d < 50.f || twp->wtimer >= 1) {
    NJS_VECTOR sp14 = playertwp[r0]->cwp->info->center;
    f32 v;
    int stackpad[2];

    if (d > 50.f) {
      d = 50.f;
    }
    v = d * 1.3f / 50.f;

    if (v > 5.0f) {
      v = 5.0f;
    } else if (v < 0.85f) {
      v = 0.85f;
    }
    v *= (1.0f + njScalor(&pwp->spd) * 0.5f);

    CalcAdvanceAsPossible(&twp->pos, &sp14, v, &twp->pos);
    twp->wtimer++;
  }
  GET_RING_FWK(tp)->_4 += 3.0f;
  CCL_Entry(tp);
  return TRUE;
}

static s16 _rename_defaultRingModel_s16_list[] = {
#include "assets/_rename_defaultRingModel_s16_list.inc"
};

static s32 _rename_defaultRingModel_s32_list[] = {
#include "assets/_rename_defaultRingModel_s32_list.inc"
};

static NJS_CNK_MODEL _rename_defaultRingModel = {
    _rename_defaultRingModel_s32_list,
    _rename_defaultRingModel_s16_list,
    {0, 0, -0.f},
    3.102889060974121f};

static NJS_CNK_OBJECT _rename_defaultRingObject = {
    22,  &_rename_defaultRingModel, {0, 0, 0}, {0, 0, 0}, {1, 1, 1}, NULL, NULL,
    0.f,
};

static ringwk *CreateRingObject() {
  ringwk *wk = syCalloc(1, sizeof(ringwk));
  if (wk != NULL) {
    CreateRingTask();
    wk->cnkObj = _rename_defaultRingObject;
    wk->cnkObj.evalflags &= ~(NJD_EVAL_UNIT_POS | NJD_EVAL_UNIT_ANG);
    wk->shadow_posy = -1000000.0f;
  } else {
    return NULL;
  }

  if (RingObjects != NULL) {
    wk->cnkObj.sibling = &RingObjects->cnkObj;
  }
  RingObjects = wk;
  return wk;
}

static void o_ring_10(ringwk *arg) {
  if (arg != NULL) {
    arg->cnkObj.evalflags |= NJD_EVAL_HIDE;
    arg->cnkObj.model = NULL;
    CleanupRingObjs = TRUE;
  }
}

static void RingModelDest(task *tp) {
  while (RingObjects != NULL) {
    ringwk *tmp = (ringwk *)RingObjects->cnkObj.sibling;
    syFree(RingObjects);
    RingObjects = tmp;
  }

  CleanupRingObjs = FALSE;
  if (RingTP == tp) {
    RingTP = NULL;
  }
}

static void RingModelExec(task *tp) {
  if (CleanupRingObjs) {
    ringwk *currNode = RingObjects;
    ringwk *nextNode = NULL;
    ringwk *prevNode = NULL;
    for (; currNode != NULL; currNode = nextNode) {
      nextNode = (ringwk *)currNode->cnkObj.sibling;
      if (!currNode->cnkObj.model) {
        syFree(currNode);
        if (prevNode != NULL) {
          prevNode->cnkObj.sibling = &nextNode->cnkObj;
        }
        if (RingObjects == currNode) {
          RingObjects = nextNode;
        }
      } else {
        prevNode = currNode;
      }
    }
    CleanupRingObjs = FALSE;
  }

  if (RingObjects == NULL) {
    DestroyTask(tp);
  }
}

static void RingModelDisp(task *tp) {
  ringwk *pRing;
  u8 stackpad[0x58];

  if (!lbl_801CC168._3D) {
    if (DisableObjectFog) {
      njDisableFog();
      gjSetFog();
    }
    njSetTexture(&_rename_ring_tex_0);
    njPushMatrixEx();
    pRing = RingObjects;
    for (; pRing != NULL; pRing = (ringwk *)pRing->cnkObj.sibling) {
      if ((pRing->cnkObj.evalflags & NJD_EVAL_HIDE) == 0) {
        NJS_VECTOR spC;
        f32 v;
        njCalcPoint(NULL, &pRing->cnkObj.pos, &spC);
        v = -spC.z;
        if (v > -10.0f) {
          njTranslateEx(&pRing->cnkObj.pos);
          njRotateY(NULL, pRing->cnkObj.ang.y);
          if (v < 65.0f) {
            gjDrawModel(&model_ring_l1);
          } else if (v < 130.f) {
            gjDrawModel(&model_ring_l2);
          } else {
            gjDrawModel(&model_ring);
          }
          njPopMatrixEx();
          njPushMatrixEx();
        }
      }
    }
    njPopMatrixEx();
    if (DisableObjectFog) {
      njEnableFog();
      gjSetFog();
    }
  }
}

static void RingModelDisp2(task *tp) {
  ringwk *pRing;
  if (!lbl_801CC168._3D) {
    if (DisableObjectFog) {
      njDisableFog();
      gjSetFog();
    }
    njSetTexture(&_rename_ring_tex_1);
    pRing = RingObjects;
    njPushMatrixEx();
    for (; pRing != NULL; pRing = (ringwk *)pRing->cnkObj.sibling) {
      if (pRing->shadow_posy != -1000000.0f &&
          pRing->shadow_posy != 1000000.0f) {
        njTranslate(NULL, pRing->cnkObj.pos.x, pRing->shadow_posy,
                    pRing->cnkObj.pos.z);
        njRotateZ(NULL, pRing->shadow_ang.z);
        njRotateX(NULL, pRing->shadow_ang.x);
        njRotateY(NULL, pRing->shadow_ang.y);
        njTranslate(NULL, 0.0f, 0.5f, 0.0f);
        njScale(NULL, sScaleX, 1.0f, sScaleZ);
        gjDrawModel(&_rename_ring_tex_2);
        njPopMatrixEx();
        njPushMatrixEx();
      }
    }
    njPopMatrixEx();
    if (DisableObjectFog) {
      njEnableFog();
      gjSetFog();
    }
  }
}

void CreateRingTask(void) {
  if (RingTP == NULL) {
    task *t = CreateFundamentalTask(2, 1, RingModelExec);
    if (t != NULL) {
      RingTP = t;
      t->exec = RingModelExec;
      t->disp = RingModelDisp;
      t->disp_dely = RingModelDisp2;
      t->dest = RingModelDest;
    }
  }
}
