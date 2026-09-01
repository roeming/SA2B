/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/chao/al_chao_info.h'
*
*   Description:
*       Contains functions and data related to Chao save data.
*/
#ifndef _SA2B_CHAO_CHAOINFO_H_
#define _SA2B_CHAO_CHAOINFO_H_

#define AL_MAX_SKILL 5
#define AL_MIN_SKILL -5

enum
{
    G_PER_CURIOSITY   = 0x0,
    G_PER_KINDNESS    = 0x1,
    G_PER_AGRESSIVE   = 0x2,
    G_PER_SLEEPY_HEAD = 0x3,
    G_PER_SOLITUDE    = 0x4,
    G_PER_VITALITY    = 0x5,
    G_PER_GLUTTON     = 0x6,
    G_PER_REGAIN      = 0x7,
    G_PER_SKILLFUL    = 0x8,
    G_PER_CHARM       = 0x9,
    G_PER_CHATTY      = 0xA,
    G_PER_CALM        = 0xB,
    G_PER_FICKLE      = 0xC,
    NB_G_PER          = 0xD,
};

enum
{
    TYPE_NONE     = 0x0,
    TYPE_EGG      = 0x1,
    TYPE_CHILD    = 0x2,
    TYPE_DUMMY1   = 0x3,
    TYPE_DUMMY2   = 0x4,
    TYPE_N_NORMAL = 0x5,
    TYPE_H_NORMAL = 0x6,
    TYPE_D_NORMAL = 0x7,
    TYPE_N_SWIM   = 0x8,
    TYPE_H_SWIM   = 0x9,
    TYPE_D_SWIM   = 0xA,
    TYPE_N_FLY    = 0xB,
    TYPE_H_FLY    = 0xC,
    TYPE_D_FLY    = 0xD,
    TYPE_N_RUN    = 0xE,
    TYPE_H_RUN    = 0xF,
    TYPE_D_RUN    = 0x10,
    TYPE_N_POWER  = 0x11,
    TYPE_H_POWER  = 0x12,
    TYPE_D_POWER  = 0x13,
    TYPE_N_CHAOS  = 0x14,
    TYPE_H_CHAOS  = 0x15,
    TYPE_D_CHAOS  = 0x16,
    TYPE_TAILS    = 0x17,
    TYPE_KNUCKLES = 0x18,
    TYPE_AMY      = 0x19,
    TYPE_MINIMAL  = 0x1A,
    TYPE_OMOCHAO  = 0x1B,
    TYPE_EGG_FOOT = 0x1C,
};


enum
{
    SKILL_SWIM      = 0x0,
    SKILL_FLY       = 0x1,
    SKILL_RUN       = 0x2,
    SKILL_POWER     = 0x3,
    SKILL_STAMINA   = 0x4,
    SKILL_GUTS      = 0x5,
    SKILL_INTELLECT = 0x6,
    SKILL_EMPTY     = 0x7,
    NB_SKILL        = 0x8,
};

/************************/
/*  Structures          */
/************************/
typedef struct
{
    u32 gid[2];
    u32 id[2];
    u32 num;
}
CHAO_ID;

typedef struct
{
    f32 HPos;            // Run : Power Align
    f32 VPos;            // Swim : Fly Align
    f32 APos;            // Dark : Hero Align
    f32 AimHPos;        // Last Run : Power
    f32 AimVPos;        // Last Swim : Fly
    f32 AimAPos;        // Last Alignment
    f32 growth;        // Magitude
    f32 EyePos;
    f32 EyeScl;
    f32 EyeRatio;
    u8 EyeColor;
    u8 DefaultEyeNum;
    u8 DefaultMouthNum;
    u8 HonbuNum;        // Icon kind
    u8 HonbuColorNum;    // Inert
    u8 ObakeHead;        // Hat / Mask
    u8 ObakeBody;        // Hide Feet
    u8 MedalNum;
    u8 ColorNum;
    u8 NonTex;            // isMonotone
    u8 JewelNum;
    u8 MultiNum;        // Shiny
    s8 EggColor;
    u8 FormNum;
    u8 FormSubNum;        // Animal
    u8 UNDEF0;
}
AL_BODY_INFO;

typedef struct
{
    u8 minute;
    u8 second;
    u8 frame;
}
AL_TIME;

typedef struct
{
    AL_TIME PersonalRecord[10];
    u8 nbWin[10];
    u16 MedalFlag;
}
AL_RACE_PERSONAL_INFO;

typedef struct
{
    u8 rank;
    u8 level;
    u8 tournament;
    u8 UNDEF0;
    u16 nbBattle;
    u16 nbWin;
    u16 nbLose;
    u16 nbDraw;
}
AL_KARATE_PERSONAL_INFO;

typedef struct 
{
    u32 MinimalFlag;
    s8 MinimalParts[8];
}
AL_PARTS;

typedef struct
{
    /* 0x00 */ u16 Flag;
    /* 0x02 */ u16 MoodTimer;
    /* 0x04 */ u16 IllTimer;
    /* 0x06 */ u16 loc_timer;
    /* 0x08 */ u8 Mood[8];
    /* 0x10 */ u16 State[11];
    /* 0x26 */ s8 Personality[NB_G_PER];
    /* 0x33 */ u8 Taste;
    /* 0x34 */ u8 Tv;
    /* 0x35 */ u8 Music;
    /* 0x36 */ s8 IllState[6];
}
AL_EMOTION;

typedef struct
{
    s8 like;
    u8 fear;
    u16 distance;
    u16 meet;
}
AL_KNOWLEDGE_PLAYER;

typedef struct
{
    CHAO_ID id;
    s8 like;
    u8 fear;
    u16 distance;
    u16 meet;
    u8 UNDEF0;
    u8 UNDEF1;
}
AL_KNOWLEDGE_CHAO;

typedef struct
{
    s8 like;
}
AL_KNOWLEDGE_OTHER;

typedef struct
{
    u8 ArtFlag;
    u8 DanceFlag;
    u8 SongFlag;
    u8 MusicFlag;
    u16 SToyFlag;
    u16 LToyFlag;
    s32 KwTimer;
    AL_KNOWLEDGE_PLAYER player[6];
    AL_KNOWLEDGE_CHAO chao[20];
    AL_KNOWLEDGE_OTHER bhv[120];
}
AL_KNOWLEDGE_BTL;

typedef struct al_gene
{
    /* 0x00 */ s8 IsAnalyzed;
    /* 0x01 */ s8 EggColor;
    /*      */ // pad 2 bytes
    /* 0x04 */ CHAO_ID MotherID;
    /* 0x18 */ CHAO_ID FatherID;
    /* 0x2C */ char MotherName[8];
    /* 0x34 */ char FatherName[8];
    /* 0x3C */ char MGroundMotherName[8];
    /* 0x44 */ char MGroundFatherName[8];
    /* 0x4C */ char FGroundMotherName[8];
    /* 0x54 */ char FGroundFatherName[8];
    /* 0x5C */ u8 Abl[8][2];
    /* 0x6C */ u8 LifeTime[2];
    /* 0x6E */ s8 HPos[2]; // run : power
    /* 0x70 */ s8 VPos[2]; // swim : flight
    /* 0x72 */ s8 APos[2]; // alignment dark : hero
    /* 0x74 */ s8 Personality[NB_G_PER][2];
    /* 0x8E */ u8 Taste[2];
    /* 0x90 */ u8 Tv[2];
    /* 0x92 */ u8 Music[2];
    /* 0x94 */ u8 Color[2];
    /* 0x96 */ u8 NonTex[2];    // Monotone
    /* 0x98 */ u8 Jewel[2];
    /* 0x9A */ u8 Multi[2];    // Shiny
    /* 0x9C */ u8 EyePos[2];
    /* 0x9E */ u8 EyeScl[2];
    /* 0xA0 */ u8 EyeRatio[2];
    /* 0xA2 */ u8 EyeColor[2];
}
AL_GENE;

typedef struct
{
    AL_TIME PersonalRecord[5];
}
AL_RACE_PERSONAL_INFO_DX;

typedef struct 
{
    AL_KNOWLEDGE_PLAYER player[6];
}
AL_KNOWLEDGE_DX;

typedef struct chao_param_gc
{
    /* 0x000 */ u8 GBAChao;
    /* 0x001 */ u8 GBAEgg;
    /* 0x002 */ u8 GBABerry[8];
    /* 0x00A */ u8 padding0;
    /* 0x00B */ u8 padding1;
    /* 0x00C */ u32 GBARing;                // Rings moving from GBA -> GCN
    /* 0x010 */ u8 BootMethed;
    /* 0x011 */ u8 Birthplace;
    /* 0x012 */ u8 name[7];
    /* 0x019 */ u8 GBAType;
    /* 0x01A */ u8 GBASkin;
    /* 0x01B */ u8 GBAMood;
    /* 0x01C */ u8 GBABelly;
    /* 0x01D */ u8 GBASleepy;
    /* 0x01E */ u8 GBALonelyness;
    /* 0x01F */ u8 padding2;
    /* 0x020 */ u8 Exp[8];                // Progress 0 - 100
    /* 0x028 */ u8 Abl[8];                // Grade E - S
    /* 0x030 */ u8 Lev[8];                // Level 0 - 99
    /* 0x038 */ u16 Skill[8];            // Total Points
    /* 0x048 */ u16 GBAPallete[16];
    /* 0x068 */ u8 rmsg[16];
    /* 0x078 */ u32 runaway;
    /* 0x07C */ u8 dummy[4];
    /* 0x080 */ u8 type;                    // Chao Type
    /* 0x081 */ u8 place;                // Chao Area
    /* 0x082 */ s16 like;                // Happiness
    /* 0x084 */ s8 ClassNum;
    /* 0x086 */ u16 age;                    // total clock rollovers
    /* 0x088 */ u16 old;                    // adult clock rollovers
    /* 0x08A */ u16 life;                // Liftime1
    /* 0x08C */ u16 LifeMax;                // Liftime2
    /* 0x08E */ u16 nbSucceed;            // reincarnations
    /* 0x090 */ CHAO_ID ChaoID;
    /* 0x0A4 */ u32 LifeTimer;
    /* 0x0A8 */ AL_BODY_INFO body;
    /* 0x0E0 */ AL_RACE_PERSONAL_INFO race;
    /* 0x10A */ AL_KARATE_PERSONAL_INFO karate;
    /* 0x118 */ AL_PARTS PartsBTL;
    /* 0x124 */ AL_EMOTION emotion;
    /* 0x160 */ AL_KNOWLEDGE_BTL knowledge;
    /* 0x438 */ AL_GENE gene;
    /* 0x4DC */ BOOL     IsInitializedDX;
    /* 0x4E0 */ AL_PARTS partsDX;
    /* 0x4EC */ AL_RACE_PERSONAL_INFO_DX raceDX;
    /* 0x4FC */ AL_KNOWLEDGE_DX knowledgeDX;
}
CHAO_PARAM_GC;

typedef struct chao_save_info
{
    CHAO_PARAM_GC param;
    u8 dummy[736];
}
CHAO_SAVE_INFO;

/************************/
/*  Data                */
/************************/
#define pSelectedChaoSaveInfoList   DATA_REF(CHAO_SAVE_INFO*, 0x01A5CC00)
#define pHoldingChaoSaveInfo        DATA_REF(CHAO_SAVE_INFO*, 0x01A5CA5C)
#define HoldingFront                DATA_REF(BOOL       , 0x01A5CAB4)

#define ChaoSetPositionNeut         DATA_ARY(NJS_POINT3     , 0x01366260, [16])
#define ChaoSetPositionHero         DATA_ARY(NJS_POINT3     , 0x01366320, [16])
#define ChaoSetPositionDark         DATA_ARY(NJS_POINT3     , 0x013663E0, [16])

/************************/
/*  Functions           */
/************************/
EXTERN_START
CHAO_SAVE_INFO* AL_GetNewChaoSaveInfo(void);

void    AL_SetChaoOnTheGarden(void);
void    AL_CreateHoldingChao(void);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define AL_GetNewChaoSaveInfo_p      FUNC_PTR(CHAO_SAVE_INFO*, __cdecl, (void), 0x00531AA0)
#   define AL_SetChaoOnTheGarden_p      FUNC_PTR(void           , __cdecl, (void), 0x00531B10)
#   define AL_CreateHoldingChao_p       FUNC_PTR(void           , __cdecl, (void), 0x00531E10)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_CHAOINFO_H_*/
