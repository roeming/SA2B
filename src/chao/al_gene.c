#include "chao/al_gene.h"
#include "Dolphin/os.h"
#include "PowerPC_EABI_Support\MSL_C\MSL_Common\rand.h"
#include "math.h"
#include "samt/sonic/chao/al_egg.h"
#include "samt/sonic/chao/al_emotion.h"
#include "samt/sonic/chao/al_garden_info.h"
#include "samt/sonic/chao/al_global.h"
#include "samt/sonic/chao/chao.h"

extern u8 eye_default_num[3][3][3];
extern u8 mouse_default_num[3][3][3];

extern int AL_GetPreStageNumber();
extern int AL_GetStageNumber();
extern void AL_ClearParts(task *);
extern GARDEN_ID *_rename_AL_GetCurrGarden();
extern CHAO_GARDEN_INFO *AL_GetGardenInfo();
extern BOOL AL_IsHero(u8 type);
extern BOOL AL_IsDark(u8 type);
#define njRandom() (rand() * (1.f / 32768.f))

// ^ extern
// v in this file

#define INLINE_BZERO(p, size)                                                  \
  {                                                                            \
    int i;                                                                     \
    for (i = 0; i < (size); i++)                                               \
      ((u8 *)(p))[i] = 0;                                                      \
  }

#define RAND_RANGE(maxVal) (njRandom() * (maxVal))
#define RAND_S32(maxIndex) (s32)(RAND_RANGE((maxIndex) - 1e-4f))
#define RAND_U32(maxIndex) (u32)(RAND_RANGE((maxIndex) - 1e-4f))
#define RAND_BOOL() (int)RAND_RANGE(1.99f)

void AL_GeneCreatePlane(AL_GENE *pGene) {
  AL_GeneCreate(pGene);

  // feels like a mult by 0, but it messes up the stack
  rand();
  pGene->Personality[G_PER_KINDNESS][0] =
      pGene->Personality[G_PER_KINDNESS][1] = 0;

  rand();
  pGene->Personality[G_PER_AGRESSIVE][0] =
      pGene->Personality[G_PER_AGRESSIVE][1] = 0;

  rand();
  pGene->Personality[G_PER_CURIOSITY][0] =
      pGene->Personality[G_PER_CURIOSITY][1] = 0;
}

void AL_GeneCreate(AL_GENE *pGene) {
  f32 randVal;
  int i = 0;
  INLINE_BZERO(pGene, sizeof(*pGene));
  pGene->IsAnalyzed = FALSE;
  randVal = njRandom();
  if (randVal < 0.33f) {
    int arr[] = {0, 1, 2, 3, 4};
    for (i = 0; i < 10; i++) {
      u32 index1 = RAND_U32(ARRAY_COUNT(arr));
      u32 index2 = RAND_U32(ARRAY_COUNT(arr));
      int tmp = arr[index1];
      arr[index1] = arr[index2];
      arr[index2] = tmp;
    }

    // @BUG: arr only has 5 values, and pGene->abl has 8 values
    for (i = 0; i < ARRAY_COUNT(pGene->Abl); i++) {
      pGene->Abl[i][0] = pGene->Abl[i][1] = arr[i];
    }
  } else if (randVal < 0.66f) {
    for (i = 0; i < ARRAY_COUNT(pGene->Abl); i++) {
      pGene->Abl[i][0] = pGene->Abl[i][1] = RAND_U32(3) + 1;
    }
  } else {
    for (i = 0; i < ARRAY_COUNT(pGene->Abl); i++) {
      pGene->Abl[i][0] = pGene->Abl[i][1] = 0;
    }

    i = 0;
    while (TRUE) {
      u32 ind = RAND_U32(ARRAY_COUNT(pGene->Abl));
      if (pGene->Abl[ind][0] < AL_MAX_SKILL) {
        pGene->Abl[ind][0]++;
        pGene->Abl[ind][1]++;
        i++;
        if (i >= 14)
          break;
      }
    }
  }

  pGene->LifeTime[0] = RAND_U32(10);
  pGene->LifeTime[1] = RAND_U32(10);
  for (i = 0; i < ARRAY_SIZE(pGene->HPos); i++) {
    pGene->HPos[i] = 0;
  }
  for (i = 0; i < ARRAY_SIZE(pGene->VPos); i++) {
    pGene->VPos[i] = 0;
  }
  for (i = 0; i < ARRAY_SIZE(pGene->APos); i++) {
    pGene->APos[i] = 0;
  }

  for (i = 0; i < ARRAY_COUNT(pGene->Personality); i++) {
    pGene->Personality[i][0] = RAND_U32(5);
    pGene->Personality[i][1] = RAND_U32(5);
  }
  pGene->Taste[0] = RAND_U32(6);
  pGene->Taste[1] = RAND_U32(6);
  pGene->Tv[0] = RAND_U32(6);
  pGene->Tv[1] = RAND_U32(6);
  pGene->Music[0] = RAND_U32(6);
  pGene->Music[1] = RAND_U32(6);
  pGene->Color[0] = 0;
  pGene->Color[1] = 0;
  pGene->NonTex[0] = 0;
  pGene->NonTex[1] = 0;
  pGene->Jewel[0] = 0;
  pGene->Jewel[1] = 0;
  pGene->Multi[0] = 0;
  pGene->Multi[1] = 0;
}

void AL_GeneCreateGBA(AL_GENE *pGene, CHAO_PARAM_GC *pParam) {
  int i = 0;
  INLINE_BZERO(pGene, sizeof(*pGene));
  pGene->IsAnalyzed = FALSE;

  for (i = 0; i < ARRAY_COUNT(pGene->Abl); i++) {
    pGene->Abl[i][0] = pGene->Abl[i][1] = pParam->Abl[i];
  }

  pGene->LifeTime[0] = RAND_U32(10);
  pGene->LifeTime[1] = RAND_U32(10);
  for (i = 0; i < ARRAY_SIZE(pGene->HPos); i++) {
    pGene->HPos[i] = 0;
  }
  for (i = 0; i < ARRAY_SIZE(pGene->VPos); i++) {
    pGene->VPos[i] = 0;
  }
  for (i = 0; i < ARRAY_SIZE(pGene->APos); i++) {
    pGene->APos[i] = 0;
  }
  {
    int i;
    for (i = 0; i < ARRAY_COUNT(pGene->Personality); i++) {
      pGene->Personality[i][0] = RAND_U32(5);
      pGene->Personality[i][1] = RAND_U32(5);
    }
  }
  pGene->Taste[0] = RAND_U32(6);
  pGene->Taste[1] = RAND_U32(6);
  pGene->Tv[0] = RAND_U32(6);
  pGene->Tv[1] = RAND_U32(6);
  pGene->Music[0] = RAND_U32(6);
  pGene->Music[1] = RAND_U32(6);
  pGene->Color[0] = 0;
  pGene->Color[1] = 0;
  pGene->NonTex[0] = 0;
  pGene->NonTex[1] = 0;

  if (pParam->GBASkin != 0 && pParam->GBASkin < 12) {
    pGene->Jewel[0] = pGene->Jewel[1] = pParam->GBASkin;
  } else {
    pGene->Jewel[0] = 0;
    pGene->Jewel[1] = 0;
  }

  pGene->Multi[0] = 0;
  pGene->Multi[1] = 0;
}

void AL_GeneCreateGBAEgg(AL_GENE *pGene, CHAO_PARAM_GC *pParam) {
  f32 randVal;
  int i = 0;
  INLINE_BZERO(pGene, sizeof(*pGene));
  pGene->IsAnalyzed = FALSE;
  randVal = njRandom();
  if (randVal < 0.33f) {
    int arr[] = {0, 1, 2, 3, 4};
    for (i = 0; i < 10; i++) {
      u32 index1 = RAND_U32(ARRAY_COUNT(arr));
      u32 index2 = RAND_U32(ARRAY_COUNT(arr));
      int tmp = arr[index1];
      arr[index1] = arr[index2];
      arr[index2] = tmp;
    }

    // @BUG: arr only has 5 values, and pGene->abl has 8 values
    for (i = 0; i < ARRAY_COUNT(pGene->Abl); i++) {
      pGene->Abl[i][0] = pGene->Abl[i][1] = arr[i];
    }
  } else if (randVal < 0.66f) {
    for (i = 0; i < ARRAY_COUNT(pGene->Abl); i++) {
      pGene->Abl[i][0] = pGene->Abl[i][1] = RAND_U32(3) + 1;
    }
  } else {
    for (i = 0; i < ARRAY_COUNT(pGene->Abl); i++) {
      pGene->Abl[i][0] = pGene->Abl[i][1] = 0;
    }

    i = 0;
    while (TRUE) {
      u32 ind = RAND_U32(ARRAY_COUNT(pGene->Abl));
      if (pGene->Abl[ind][0] < AL_MAX_SKILL) {
        pGene->Abl[ind][0]++;
        pGene->Abl[ind][1]++;
        i++;
        if (i >= 14)
          break;
      }
    }
  }

  pGene->LifeTime[0] = RAND_U32(10);
  pGene->LifeTime[1] = RAND_U32(10);
  for (i = 0; i < ARRAY_SIZE(pGene->HPos); i++) {
    pGene->HPos[i] = 0;
  }
  for (i = 0; i < ARRAY_SIZE(pGene->VPos); i++) {
    pGene->VPos[i] = 0;
  }
  for (i = 0; i < ARRAY_SIZE(pGene->APos); i++) {
    pGene->APos[i] = 0;
  }
  {
    // int i;
    for (i = 0; i < ARRAY_COUNT(pGene->Personality); i++) {
      pGene->Personality[i][0] = RAND_U32(5);
      pGene->Personality[i][1] = RAND_U32(5);
    }
  }
  pGene->Taste[0] = RAND_U32(6);
  pGene->Taste[1] = RAND_U32(6);
  pGene->Tv[0] = RAND_U32(6);
  pGene->Tv[1] = RAND_U32(6);
  pGene->Music[0] = RAND_U32(6);
  pGene->Music[1] = RAND_U32(6);
  pGene->Color[0] = 0;
  pGene->Color[1] = 0;
  pGene->NonTex[0] = 0;
  pGene->NonTex[1] = 0;

  if (pParam->GBASkin != 0 && pParam->GBASkin < 12) {
    pGene->Jewel[0] = pGene->Jewel[1] = pParam->GBAEgg;
  } else {
    pGene->Jewel[0] = 0;
    pGene->Jewel[1] = 0;
  }

  pGene->Multi[0] = 0;
  pGene->Multi[1] = 0;
}

void AL_GeneCreate_Hero(AL_GENE *pGene) {
  AL_GeneCreate(pGene);
  pGene->APos[1] = pGene->APos[0] = AL_MAX_SKILL;
}

void AL_GeneCreate_Dark(AL_GENE *pGene) {
  AL_GeneCreate(pGene);
  pGene->APos[1] = pGene->APos[0] = AL_MIN_SKILL;
}

void AL_EmotionStateInit(AL_EMOTION *pEmotion) {
  // @BUG
  // these are all bugged
  // we're indexing starting at EM_ST_SLEEPY=8, but there are only 11 states
  // so we're overwriting other fields of this struct
  // also not initalizing states 0-7
  pEmotion->State[EM_ST_SLEEPY] = (u32)RAND_RANGE(5000.0f);
  pEmotion->State[EM_ST_SLEEP_DEPTH] = 0;
  pEmotion->State[EM_ST_HUNGER] = 3000 + (u32)RAND_RANGE(6000.0f);
  pEmotion->State[EM_ST_BREED] = RAND_U32(1000);
  pEmotion->State[EM_ST_TEDIOUS] = (u32)RAND_RANGE(5000.0f);
  pEmotion->State[EM_ST_LONELY] = RAND_U32(
      0); // bug? multiplies by -0.0001, should always round to 0, but weird
  pEmotion->State[EM_ST_TIRE] = (u32)RAND_RANGE(8000.0f);
  pEmotion->State[EM_ST_STRESS] = 0;
  pEmotion->State[EM_ST_THIRSTY] = 0;
  pEmotion->State[EM_ST_NOURISHMENT] = ChaoGlobal.EmotionStateLimit;
  pEmotion->State[EM_ST_CONDITION] = ChaoGlobal.EmotionStateLimit;
}

void AL_SucceedGeneParam(AL_GENE *pGene, CHAO_PARAM_GC *pParam) {
  int i;
  for (i = 0; i < ARRAY_COUNT(pParam->Skill); i++) {
    pParam->Exp[i] = 0;
    pParam->Lev[i] = 1;
    if (pParam->Skill[i] > 5000) {
      pParam->Skill[i] = 5000;
    }
    pParam->Skill[i] = pParam->Skill[i] / 10;
  }

  for (i = 0; i < NB_G_PER; i++) {
    pGene->Personality[i][RAND_BOOL()] =
        2 + (pParam->emotion.Personality[i] / 40);
  }

  pParam->PartsBTL.MinimalFlag = 0;
  for (i = 0; i < ARRAY_COUNT(pParam->PartsBTL.MinimalParts); i++) {
    if (njRandom() < 0.3f) {
      pParam->PartsBTL.MinimalParts[i] = -1;
    }
  }

  {
    AL_EMOTION *emot = &pParam->emotion;
    // @BUG, this should be indexed by i
    for (i = 0; i < ARRAY_COUNT(emot->Mood); i++) {
      emot->Mood[8] = 0;
    }
    AL_EmotionStateInit(emot);

    for (i = 0; i < NB_G_PER; i++) {
      emot->Personality[i] = (pGene->Personality[i][RAND_BOOL()] - 2) * 40;
    }
  }

  if (pGene->LifeTime[0] >= pGene->LifeTime[1]) {
    pParam->life = pParam->LifeMax =
        ChaoGlobal.InitBaseLife +
        (pGene->LifeTime[0] * ChaoGlobal.InitMulLife) + pParam->LifeMax / 10;
  } else {
    pParam->life = pParam->LifeMax =
        ChaoGlobal.InitBaseLife +
        (pGene->LifeTime[1] * ChaoGlobal.InitMulLife) + pParam->LifeMax / 10;
  }

  pParam->old = pParam->age = 0;

  if (AL_IsHero(pParam->type)) {
    pParam->body.APos = 1.f;
  } else if (AL_IsDark(pParam->type)) {
    pParam->body.APos = -1.f;
  } else {
    pParam->body.APos = 0.f;
  }

  pParam->body.HPos = 0.f;
  pParam->body.VPos = 0.f;

  pParam->body.AimAPos = pParam->body.APos;
  pParam->body.AimHPos = pParam->body.HPos;
  pParam->body.AimVPos = pParam->body.VPos;

  pParam->body.growth = 0.f;
}

void AL_AblLevelUp(int skill, AL_GENE *pGene, CHAO_PARAM_GC *pParam) {
  if (pParam->Abl[skill] < AL_MAX_SKILL) {
    if (pGene->Abl[skill][0] == pParam->Abl[skill]) {
      pGene->Abl[skill][0]++;
    } else if (pGene->Abl[skill][1] == pParam->Abl[skill]) {
      pGene->Abl[skill][1]++;
    }
    pParam->Abl[skill]++;
  }
}

void AL_GrowGeneParam(AL_GENE *pGene, CHAO_PARAM_GC *pParam) {
  switch (pParam->type) {
  case TYPE_N_NORMAL:
  case TYPE_H_NORMAL:
  case TYPE_D_NORMAL:
    AL_AblLevelUp(SKILL_STAMINA, pGene, pParam);
    break;
  case TYPE_N_SWIM:
  case TYPE_H_SWIM:
  case TYPE_D_SWIM:
    AL_AblLevelUp(SKILL_SWIM, pGene, pParam);
    break;
  case TYPE_N_FLY:
  case TYPE_H_FLY:
  case TYPE_D_FLY:
    AL_AblLevelUp(SKILL_FLY, pGene, pParam);
    break;
  case TYPE_N_RUN:
  case TYPE_H_RUN:
  case TYPE_D_RUN:
    AL_AblLevelUp(SKILL_RUN, pGene, pParam);
    break;
  case TYPE_N_POWER:
  case TYPE_H_POWER:
  case TYPE_D_POWER:
    AL_AblLevelUp(SKILL_POWER, pGene, pParam);
    break;
  case TYPE_N_CHAOS:
  case TYPE_H_CHAOS:
  case TYPE_D_CHAOS:
    AL_AblLevelUp(SKILL_STAMINA, pGene, pParam);
    break;
  }
}

void AL_BlendGene(AL_GENE *pSrcGene1, AL_GENE *pSrcGene2, AL_GENE *pDstGene) {
#define BLEND(dst, src1, src2, field)                                          \
  (dst)->field[0] = (src1)->field[RAND_BOOL()];                                \
  (dst)->field[1] = (src2)->field[RAND_BOOL()]

  int i;
  INLINE_BZERO(pDstGene, sizeof(*pDstGene));

  for (i = 0; i < ARRAY_COUNT(pDstGene->Abl); i++) {
    BLEND(pDstGene, pSrcGene1, pSrcGene2, Abl[i]);
  }

  BLEND(pDstGene, pSrcGene1, pSrcGene2, LifeTime);
  BLEND(pDstGene, pSrcGene1, pSrcGene2, HPos);
  BLEND(pDstGene, pSrcGene1, pSrcGene2, VPos);
  BLEND(pDstGene, pSrcGene1, pSrcGene2, APos);

  for (i = 0; i < ARRAY_COUNT(pDstGene->Personality); i++) {
    BLEND(pDstGene, pSrcGene1, pSrcGene2, Personality[i]);
  }
  BLEND(pDstGene, pSrcGene1, pSrcGene2, Taste);
  BLEND(pDstGene, pSrcGene1, pSrcGene2, Tv);
  BLEND(pDstGene, pSrcGene1, pSrcGene2, Music);
  BLEND(pDstGene, pSrcGene1, pSrcGene2, Color);
  BLEND(pDstGene, pSrcGene1, pSrcGene2, NonTex);
  BLEND(pDstGene, pSrcGene1, pSrcGene2, Jewel);
  BLEND(pDstGene, pSrcGene1, pSrcGene2, Multi);

#undef BLEND
}

void AL_CreateChildGene(task *pMotherTask, task *pFatherTask,
                        AL_GENE *pChildGene) {
  // fake? this is a crazy amount of stack padding
  u8 pad[0x9C0];

  AL_GENE *motherParam = &GET_CHAOWK(pMotherTask)->pParamGC->gene;
  AL_GENE *fatherParam = &GET_CHAOWK(pFatherTask)->pParamGC->gene;
  AL_GENE mother = *motherParam;
  AL_GENE father = *fatherParam;
  AL_BlendGene(&mother, &father, pChildGene);
}

void AL_GeneAnalyzeCommon(AL_GENE *pGene, CHAO_PARAM_GC *pParam) {
  AL_EMOTION *emot = &pParam->emotion;
  CHAO_ID *id = &pParam->ChaoID;
  int i;

  pGene->IsAnalyzed = TRUE;
  pParam->type = 2;
  pParam->ClassNum = -1;
  {
    GARDEN_ID *info = _rename_AL_GetCurrGarden();
    id->gid[0] = info->id[0];
    id->gid[1] = info->id[1];
  }
  id->id[0] = OSGetTick();
  id->id[1] = 0;
  id->num = AL_GetGardenInfo()->nbBorn++;

  pParam->Skill[SKILL_STAMINA] = 0;
  for (i = 0; i < ARRAY_COUNT(pParam->Abl); i++) {
    int v;
    if (pGene->Abl[i][0] >= pGene->Abl[i][1]) {
      if (njRandom() < 0.7f) {
        v = pGene->Abl[i][0];
      } else {
        v = pGene->Abl[i][1];
      }
    } else {
      if (njRandom() < 0.7f) {
        v = pGene->Abl[i][1];
      } else {
        v = pGene->Abl[i][0];
      }
    }
    pParam->Abl[i] = v;
  }

  if (pGene->LifeTime[0] >= pGene->LifeTime[1]) {
    pParam->life = pParam->LifeMax =
        ChaoGlobal.InitBaseLife + pGene->LifeTime[0] * ChaoGlobal.InitMulLife;
  } else {
    pParam->life = pParam->LifeMax =
        ChaoGlobal.InitBaseLife + pGene->LifeTime[1] * ChaoGlobal.InitMulLife;
  }
  pParam->body.HPos = pGene->HPos[RAND_U32(2)] * ChaoGlobal.InitMulForm;
  pParam->body.VPos = pGene->VPos[RAND_U32(2)] * ChaoGlobal.InitMulForm;
  pParam->body.APos = pGene->APos[RAND_U32(2)] * ChaoGlobal.InitMulAttr;

  AL_EmotionStateInit(emot);
  for (i = 0; i < ARRAY_COUNT(pGene->Personality); i++) {
    emot->Personality[i] = (pGene->Personality[i][RAND_BOOL()] - 2) * 40;
  }
  emot->Taste = pGene->Taste[RAND_U32(2)];
  emot->Tv = pGene->Tv[RAND_U32(2)];
  emot->Music = pGene->Music[RAND_U32(2)];
  {
    int kind, agg, cur;
    if (emot->Personality[G_PER_KINDNESS] < -45) {
      kind = 0;
    } else if (emot->Personality[G_PER_KINDNESS] < 45) {
      kind = 1;
    } else {
      kind = 2;
    }
    if (emot->Personality[G_PER_AGRESSIVE] < -45) {
      agg = 0;
    } else if (emot->Personality[G_PER_AGRESSIVE] < 45) {
      agg = 1;
    } else {
      agg = 2;
    }
    if (emot->Personality[G_PER_CURIOSITY] < -45) {
      cur = 0;
    } else if (emot->Personality[G_PER_CURIOSITY] < 45) {
      cur = 1;
    } else {
      cur = 2;
    }
    pParam->body.DefaultEyeNum = eye_default_num[agg][kind][cur];
    pParam->body.DefaultMouthNum = mouse_default_num[agg][kind][cur];
  }

  if (pGene->EggColor) {
    u8 eggColor = pGene->EggColor;
    int color, jewel, nonTex, multi;
    switch (eggColor) {
    case EggColor_Normal:
      break;
    case EggColor_Yellow:
    case EggColor_White:
    case EggColor_Brown:
    case EggColor_SkyBlue:
    case EggColor_Pink:
    case EggColor_Blue:
    case EggColor_Gray:
    case EggColor_Green:
    case EggColor_Red:
    case EggColor_AppleGreen:
    case EggColor_Purple:
    case EggColor_Orange:
    case EggColor_Black:
      color = eggColor & 0xff;
      jewel = FALSE;
      nonTex = TRUE;
      multi = FALSE;
      break;
    case EggColor_BlendYellow:
    case EggColor_BlendWhite:
    case EggColor_BlendBrown:
    case EggColor_BlendSkyBlue:
    case EggColor_BlendPink:
    case EggColor_BlendBlue:
    case EggColor_BlendGray:
    case EggColor_BlendGreen:
    case EggColor_BlendRed:
    case EggColor_BlendAppleGreen:
    case EggColor_BlendPurple:
    case EggColor_BlendOrange:
    case EggColor_BlendBlack:
      color = eggColor - EggColor_BlendYellow + 1;
      jewel = FALSE;
      nonTex = FALSE;
      multi = FALSE;
      break;
    case EggColor_ShinyNormal:
      color = AL_COLOR_NORMAL;
      jewel = FALSE;
      nonTex = FALSE;
      multi = TRUE;
      break;
    case EggColor_ShinyYellow:
    case EggColor_ShinyWhite:
    case EggColor_ShinyBrown:
    case EggColor_ShinySkyBlue:
    case EggColor_ShinyPink:
    case EggColor_ShinyBlue:
    case EggColor_ShinyGray:
    case EggColor_ShinyGreen:
    case EggColor_ShinyRed:
    case EggColor_ShinyAppleGreen:
    case EggColor_ShinyPurple:
    case EggColor_ShinyOrange:
    case EggColor_ShinyBlack:
      color = eggColor - EggColor_ShinyYellow + 1;
      jewel = FALSE;
      nonTex = TRUE;
      multi = TRUE;
      break;
    case EggColor_ShinyBlendYellow:
    case EggColor_ShinyBlendWhite:
    case EggColor_ShinyBlendBrown:
    case EggColor_ShinyBlendSkyBlue:
    case EggColor_ShinyBlendPink:
    case EggColor_ShinyBlendBlue:
    case EggColor_ShinyBlendGray:
    case EggColor_ShinyBlendGreen:
    case EggColor_ShinyBlendRed:
    case EggColor_ShinyBlendAppleGreen:
    case EggColor_ShinyBlendPurple:
    case EggColor_ShinyBlendOrange:
    case EggColor_ShinyBlendBlack:
      color = eggColor - EggColor_ShinyBlendYellow + 1;
      jewel = FALSE;
      nonTex = FALSE;
      multi = TRUE;
      break;
    case EggColor_Gold:
    case EggColor_Silver:
    case EggColor_Ruby:
    case EggColor_Sapphire:
    case EggColor_Emerald:
    case EggColor_Amethyst:
    case EggColor_Aquamarine:
    case EggColor_Garnet:
    case EggColor_Onyx:
    case EggColor_Peridot:
    case EggColor_Topaz:
    case EggColor_Pearl:
    // unsure that these egg colors have the correct name
    case EggColor_Env0:
    case EggColor_Env1:
    case EggColor_Env2:
      color = AL_COLOR_NORMAL;
      jewel = eggColor - EggColor_Gold + 1;
      nonTex = FALSE;
      multi = FALSE;
      break;
    }
    pGene->Color[0] = pGene->Color[1] = color;
    pGene->Jewel[0] = pGene->Jewel[1] = jewel;
    pGene->NonTex[0] = pGene->NonTex[1] = nonTex;
    pGene->Multi[0] = pGene->Multi[1] = multi;
    pParam->body.EggColor = pGene->EggColor;
    pGene->EggColor = EggColor_Normal;
  }

  if (pGene->Color[0] != AL_COLOR_NORMAL) {
    if (pGene->Color[1] != AL_COLOR_NORMAL) {
      pParam->body.ColorNum = pGene->Color[RAND_U32(2)];
    } else {
      pParam->body.ColorNum = pGene->Color[0];
    }
  } else if (pGene->Color[1] != AL_COLOR_NORMAL) {
    pParam->body.ColorNum = pGene->Color[1];
  } else {
    pParam->body.ColorNum = AL_COLOR_NORMAL;
  }

  if (pGene->Jewel[0]) {
    if (pGene->Jewel[1]) {
      pParam->body.JewelNum = pGene->Jewel[RAND_U32(2)];
    } else {
      pParam->body.JewelNum = pGene->Jewel[0];
    }
  } else if (pGene->Jewel[1]) {
    pParam->body.JewelNum = pGene->Jewel[1];
  } else {
    pParam->body.JewelNum = FALSE;
  }

  if (pGene->NonTex[RAND_U32(2)]) {
    pParam->body.NonTex = TRUE;
  } else {
    pParam->body.NonTex = FALSE;
  }

  if (pGene->Multi[0] || pGene->Multi[1]) {
    pParam->body.MultiNum = TRUE;
  } else {
    pParam->body.MultiNum = FALSE;
  }
}

void AL_GeneAnalyze2(AL_GENE *pGene, CHAO_PARAM_GC *pParam) {
  int i;
  pParam->place = AL_GetPreStageNumber();
  AL_GeneAnalyzeCommon(pGene, pParam);
  for (i = 0; i < ARRAY_COUNT(pParam->PartsBTL.MinimalParts); i++) {
    pParam->PartsBTL.MinimalParts[i] = -1;
  }
}

void AL_GeneAnalyze(task *tp) {
  CHAO_PARAM_GC *pParam = GET_CHAOWK(tp)->pParamGC;
  AL_GENE *pGene = &pParam->gene;

  pParam->place = AL_GetStageNumber();
  AL_ClearParts(tp);
  AL_GeneAnalyzeCommon(pGene, pParam);
}
