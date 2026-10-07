/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/chao/chao.h'
*
*   Description:
*       Contains typedefs, enums, structures, data, & functions related
*   directly with Chao themselves.
*/
#ifndef _SA2B_CHAO_CHAO_H_
#define _SA2B_CHAO_CHAO_H_

/************************/
/*  Includes            */
/************************/
/** Ninja **/
#include <samt/ninja/ninja.h>

/** Source **/
#include <samt/sonic/motion.h>

/** Task Work **/
#include <samt/sonic/task.h>

/** Colli Info **/
#include <samt/sonic/c_colli/ccl_info.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task                     task;
typedef struct chao_param_gc            CHAO_PARAM_GC;
typedef struct al_entry_work            ALW_ENTRY_WORK;
typedef struct al_object                AL_OBJECT;
typedef struct al_group_object_list     AL_GROUP_OBJECT_LIST;

/************************/
/*  Typedefs            */
/************************/
typedef s32 (*BHV_FUNC)(task *);

/************************/
/*  Enums               */
/************************/
typedef enum
{
    AL_COLOR_NORMAL     = 0x0,
    AL_COLOR_YELLOW     = 0x1,
    AL_COLOR_WHITE      = 0x2,
    AL_COLOR_BROWN      = 0x3,
    AL_COLOR_SKYBLUE    = 0x4,
    AL_COLOR_PINK       = 0x5,
    AL_COLOR_BLUE       = 0x6,
    AL_COLOR_GRAY       = 0x7,
    AL_COLOR_GREEN      = 0x8,
    AL_COLOR_RED        = 0x9,
    AL_COLOR_APPLEGREEN = 0xA,
    AL_COLOR_PURPLE     = 0xB,
    AL_COLOR_ORANGE     = 0xC,
    AL_COLOR_BLACK      = 0xD,
    NB_AL_COLOR         = 0xE,
}
eAL_COLOR;

typedef enum
{
    MEDAL_NONE,
    MEDAL_AQU,
    MEDAL_TOP,
    MEDAL_PER,
    MEDAL_GAR,
    MEDAL_ONY,
    MEDAL_DIA,
    MEDAL_SILVER,
    MEDAL_GOLD,
    MEDAL_HERO,
    MEDAL_DARK,
    MEDAL_PERAL,
    MEDAL_AME,
    MEDAL_EME,
    MEDAL_RUB,
    MEDAL_SAP,
}
eMEDAL_PARTS;

typedef enum
{
    AL_ILLNESS_SEKI,
    AL_ILLNESS_KUSYAMI,
    AL_ILLNESS_KAYUI,
    AL_ILLNESS_HANAMIZU,
    AL_ILLNESS_SYAKKURI,
    AL_ILLNESS_HARAITA,
    NB_AL_ILLNESS,
}
eAL_ILLNESS;

typedef enum /* Toolkit addition */
{
    CHAO_GARDEN_NONE,
    CHAO_GARDEN_NEUT,
    CHAO_GARDEN_HERO,
    CHAO_GARDEN_DARK,
    CHAO_GARDEN_SS,
    CHAO_GARDEN_EC,
    CHAO_GARDEN_MR,
}
eCHAO_GARDEN;

typedef enum
{
    HONBU_NORMAL,
    HONBU_FIRE_OBAKE,
}
eAL_HONBU_BASE;

enum
{
    MD_ICON_NORMAL,
    MD_ICON_BIKKURI,
    MD_ICON_HIRAMEKI,
    MD_ICON_HATENA,
    MD_ICON_HEART,
    MD_ICON_MOJYA,
};

enum
{
    ICON_TEX_NUM_TAMA,
    ICON_TEX_NUM_BIKKURI,
    ICON_TEX_NUM_HATENA,
    ICON_TEX_NUM_HEART,
    ICON_TEX_NUM_MOJYA,
    ICON_TEX_NUM_TOGE,
    ICON_TEX_NUM_TENSHI,
    ICON_TEX_NUM_MARU,
    ICON_TEX_NUM_BATSU,
    ICON_TEX_NUM_LIGHT,
    ICON_TEX_NUM_NONE,
};

enum
{
    AL_FORM_NORMAL,
    AL_FORM_EGG_FOOT,
    AL_FORM_OMOCHAO,
    AL_FORM_MINIMAL,
    AL_FORM_CHIBI,
};

typedef enum
{
    JewelColor_Normal,
    JewelColor_Gold,
    JewelColor_Silver,
    JewelColor_Ruby,
    JewelColor_Sapphire,
    JewelColor_Emerald,
    JewelColor_Amethyst,
    JewelColor_Aquamarine,
    JewelColor_Garnet,
    JewelColor_Onyx,
    JewelColor_Peridot,
    JewelColor_Topaz,
    JewelColor_Pearl,
    JewelColor_Env0,    // Metal_1
    JewelColor_Env1,    // Metal_2
    JewelColor_Env2,    // Glass
    JewelColor_Env3,    // Moon
    JewelColor_Env4,    // Rare Tex
}
JewelColor;

typedef enum
{
    BTL_AL_PL_SONIC = 0x0,
    BTL_AL_PL_SHADOW = 0x1,
    BTL_AL_PL_TAILS = 0x2,
    BTL_AL_PL_EGGMAN = 0x3,
    BTL_AL_PL_KNUCKLES = 0x4,
    BTL_AL_PL_ROUGE = 0x5,
    NB_BTL_AL_PLAYER = 0x6,
}
eAL_PLAYER_BTL;

typedef enum 
{
    DX_AL_PL_SONIC = 0x0,
    DX_AL_PL_TAILS = 0x1,
    DX_AL_PL_KNUCKLES = 0x2,
    DX_AL_PL_AMY = 0x3,
    DX_AL_PL_E102 = 0x4,
    DX_AL_PL_BIG = 0x5,
    NB_DX_AL_PLAYER = 0x6,
}
eAL_PLAYER_DX;

typedef enum
{
    OBAKE_BODY_PARTS_NONE = 0x0,
    OBAKE_BODY_PARTS_SPECTOR = 0x1,
    OBAKE_BODY_PARTS_END = 0x2,
}
eBODY_PARTS;

typedef enum
{
    KW_BHV_ART = 0x0,
    KW_BHV_DANCE = 0x1,
    KW_BHV_SING = 0x2,
    KW_BHV_MUSIC = 0x3,
    KW_BHV_MINI1 = 0x4,
    KW_BHV_MINI2 = 0x5,
    KW_BHV_MINI3 = 0x6,
    KW_BHV_MINI4 = 0x7,
    KW_BHV_MINI5 = 0x8,
    KW_BHV_MINI6 = 0x9,
    KW_BHV_MINI7 = 0xA,
    KW_BHV_MINI8 = 0xB,
    KW_BHV_MINI9 = 0xC,
    KW_BHV_MINI10 = 0xD,
    KW_BHV_MINI11 = 0xE,
    KW_BHV_MINI12 = 0xF,
    KW_BHV_MINI13 = 0x10,
    KW_BHV_MINI14 = 0x11,
    KW_BHV_MINI15 = 0x12,
    KW_BHV_MINI16 = 0x13,
    KW_BHV_MINI17 = 0x14,
    KW_BHV_MINI18 = 0x15,
    KW_BHV_TOY1 = 0x16,
    KW_BHV_TOY2 = 0x17,
    KW_BHV_TOY3 = 0x18,
    KW_BHV_TOY4 = 0x19,
    KW_BHV_TOY5 = 0x1A,
    KW_BHV_TOY6 = 0x1B,
    KW_BHV_TOY7 = 0x1C,
    KW_BHV_TOY8 = 0x1D,
    KW_BHV_TOY9 = 0x1E,
    KW_BHV_TOY10 = 0x1F,
    KW_BHV_TOY11 = 0x20,
    KW_BHV_FLY = 0x21,
    KW_BHV_SWIM = 0x22,
    KW_BHV_CLIMB_TREE = 0x23,
    KW_BHV_CLIMB_WALL = 0x24,
    KW_BHV_WATER = 0x25,
    KW_BHV_SWING = 0x26,
    KW_BHV_SIT = 0x27,
    KW_BHV_DENGURI = 0x28,
    KW_BHV_TOILET = 0x29,
    KW_BHV_PYON = 0x2A,
    KW_BHV_BOWLING = 0x2B,
    KW_BHV_FUKKIN = 0x2C,
    KW_BHV_SHIRIFURI = 0x2D,
    KW_BHV_OJIGI = 0x2E,
    KW_BHV_CHIWA = 0x2F,
    KW_BHV_NADERU = 0x30,
    KW_BHV_AGERU = 0x31,
    KW_BHV_TALK = 0x32,
    KW_BHV_PUNCH = 0x33,
    KW_BHV_OKOSU = 0x34,
    KW_BHV_TEFURI = 0x35,
    KW_BHV_HAKUSYU = 0x36,
    KW_BHV_SURIYORU = 0x37,
    KW_BHV_AKANBE = 0x38,
    KW_BHV_WA = 0x39,
    KW_BHV_NAGERU = 0x3A,
    KW_BHV_FIGHT = 0x3B,
    KW_BHV_IGAMI = 0x3C,
    KW_BHV_LISTEN = 0x3D,
    KW_BHV_WATCH = 0x3E,
}
eKW_BHV_KIND;

typedef enum /* Toolkit addition */
{
    CHAO_FLAGS_UseMove = 0x02,
    CHAO_FLAGS_UseMotionTable = 0x04,
    CHAO_FLAGS_HaveCollision = 0x08,
    CHAO_FLAGS_RunBehaviourHandler = 0x10,
    CHAO_FLAGS_CanJiggle = 0x20,
    CHAO_FLAGS_CanRender = 0x0200,
    CHAO_FLAGS_AnotherJiggleThing = 0x1000,
    CHAO_FLAGS_RunThinkController = 0x2000,
    CHAO_FLAGS_Timescale = 0x020000,
    CHAO_FLAGS_DrawIcon = 0x100000,
}
eCHAO_FLAGS;

enum
{
    INT_TIMER_PLAYER,
    INT_TIMER_CHAO,
    INT_TIMER_GREET,
    INT_TIMER_SING,
    INT_TIMER_MUSIC,
    INT_TIMER_DANCE,
    INT_TIMER_ART,
    INT_TIMER_TOY,
    INT_TIMER_LTOY,
    INT_TIMER_MINIMAL,
    INT_TIMER_TV,
    INT_TIMER_RADICASE,
    INT_TIMER_BOX,
    INT_TIMER_BALL,
    INT_TIMER_GOO,
    INT_TIMER_AKUBI,
    NB_INT_TIMER,
};

/************************/
/*  Structures          */
/************************/
typedef struct {
  /* 0x00 */ u8 Exp[8];
  /* 0x08 */ u8 Abl[8];
  /* 0x10 */ u8 Lev[8];
  /* 0x18 */ u16 Skills[8];
} TMP_PARAM; // size: 0x28

typedef struct
{
    s32 bhv;
}
KW_BHV_ENTRY;

typedef struct {
  /* 0x000 */ u16 Flag;
  /* 0x002 */ u16 Mode;
  /* 0x004 */ u16 SubMode;
  /* 0x006 */ u16 MoveMode;
  /* 0x008 */ s32 InterruptFlag;
  /* 0x00C */ s32 Timer;
  /* 0x010 */ s32 SubTimer;
  /* 0x014 */ s32 LimitTimer;
  /*       */ //  sint32       BehaviorTimer; // SADX Only
  /* 0x018 */ u16 Intention;
  /* 0x01A */ u16 IntentionMode;
  /* 0x01C */ u16 IntentionSubMode;
  /* 0x020 */ u32 IntentionTimer[18];
  /* 0x068 */ u32 IntervalTimer[128];
  /* 0x268 */ s32 FreeWork;
  /* 0x26C */ f32 MoveRadius;
  /* 0x270 */ NJS_POINT3 BasePos;
  /* 0x27C */ BHV_FUNC PrevFunc;
  /* 0x280 */ s32 nbBhvFuncEntry;
  /* 0x284 */ s32 CurrBhvFuncNum;
  /* 0x288 */ BHV_FUNC BhvFuncList[16];
  /* 0x2C8 */ s32 ReserveTimerList[16];
  /* 0x308 */ s32 CurrKwBhvNum;
  /* 0x30C */ KW_BHV_ENTRY KwBhvList[4];
  /* 0x31C */ u32 dummy[16];
} AL_BEHAVIOR; // size: 0x35C

typedef struct {
  /** Shape object **/
  /* 0x000 */ AL_OBJECT *pObject;
  /* 0x004 */ AL_OBJECT *CurrObjectList[40];
  
  /** Shape object lists **/
  /* 0x0A4 */ AL_GROUP_OBJECT_LIST *pObjectList;
  /* 0x0A8 */ AL_GROUP_OBJECT_LIST *pObjectListH;
  /* 0x0AC */ AL_GROUP_OBJECT_LIST *pObjectListD;
  
  /** Positions **/
  /* 0x0B0 */ NJS_POINT3 BodyPos;
  /* 0x0BC */ NJS_POINT3 HeadPos;
  /* 0x0C8 */ NJS_POINT3 LeftHandPos;
  /* 0x0D4 */ NJS_POINT3 RightHandPos;
  /* 0x0E0 */ NJS_POINT3 LeftFootPos;
  /* 0x0EC */ NJS_POINT3 RightFootPos;
  /* 0x0F8 */ NJS_POINT3 MouthPos;
  
  /** Vectors **/
  /* 0x104 */ NJS_VECTOR MouthVec;
  /* 0x110 */ NJS_VECTOR LeftEyePos;
  /* 0x11C */ NJS_VECTOR LeftEyeVec;
  /* 0x128 */ NJS_VECTOR RightEyePos;
  /* 0x134 */ NJS_VECTOR RightEyeVec;
  
  /** Left hand item **/
  /* 0x140 */ NJS_CNK_OBJECT *pLeftHandItemObject;
  /* 0x144 */ NJS_TEXLIST *pLeftHandItemTexlist;
  /* 0x148 */ f32 LeftHandItemScale;
  /* 0x14C */ f32 LeftHandItemActiveFlag;
  
  /** Right hand item **/
  /* 0x150 */ NJS_CNK_OBJECT *pRightHandItemObject;
  /* 0x154 */ NJS_TEXLIST *pRightHandItemTexlist;
  /* 0x158 */ f32 RightHandItemScale;
  /* 0x15C */ f32 RightHandItemActiveFlag;
  
  /** Shape info **/
  /* 0x160 */ s32 palette;
  /* 0x164 */ s16 Flag;
  /* 0x166 */ s16 ColorNum;
  /* 0x168 */ s16 EnvNum;
  /* 0x16C */ s32 IconColor;
  /* 0x170 */ f32 SclH;
  /* 0x174 */ f32 SclV;
  /* 0x178 */ f32 CamDist;
} AL_SHAPE; // size: 0x17c

typedef struct {
  /* 0x00 */ s32 EyeTimer;
  /* 0x04 */ s16 EyeColorNum;
  /* 0x06 */ s16 EyeCurrNum;
  /* 0x08 */ s16 EyeDefaultNum;
  /* 0x0C */ s32 MouthTimer;
  /* 0x10 */ s16 MouthCurrNum;
  /* 0x12 */ s16 MouthDefaultNum;
  /* 0x14 */ f32 EyePosX;
  /* 0x18 */ f32 EyePosY;
  /* 0x1C */ f32 EyeSclX;
  /* 0x20 */ f32 EyeSclY;
  /* 0x24 */ u32 Flag;
  /* 0x28 */ AL_OBJECT *pEyeObject[2];
  /* 0x30 */ AL_OBJECT *pMouthObject;
  /* 0x34 */ s32 EyeLidBlinkMode;
  /* 0x38 */ s32 EyeLidBlinkTimer;
  /* 0x3C */ s32 EyeLidBlinkAng;
  /* 0x40 */ s32 EyeLidExpressionMode;
  /* 0x44 */ s32 EyeLidExpressionTimer;
  /* 0x48 */ s32 EyeLidExpressionDefaultCloseAng;
  /* 0x4C */ s32 EyeLidExpressionCurrCloseAng;
  /* 0x50 */ s32 EyeLidExpressionAimCloseAng;
  /* 0x54 */ s32 EyeLidExpressionDefaultSlopeAng;
  /* 0x58 */ s32 EyeLidExpressionCurrSlopeAng;
  /* 0x5C */ s32 EyeLidExpressionAimSlopeAng;
} AL_FACE_CTRL; // size: 0x60

typedef struct {
  /* 0x00 */ u16 Mode;
  /* 0x02 */ u16 TexNum;
  /* 0x04 */ u16 Timer;
  /* 0x08 */ NJS_POINT3 Offset;
  /* 0x14 */ NJS_POINT3 Pos;
  /* 0x20 */ NJS_POINT3 Velo;
  /* 0x2C */ NJS_POINT3 Scl;
  /* 0x38 */ NJS_POINT3 SclSpd;
} AL_ICON_INFO; // size: 0x44

typedef struct {
  /* 0x00 */ s16 CurrType;
  /* 0x02 */ s16 NextType;
  /* 0x04 */ s32 Timer;
  /* 0x08 */ s32 NextTimer;
  /* 0x0C */ s32 PuniPhase;
  /* 0x10 */ s32 PosPhase;
  /* 0x14 */ u32 Color;
  /* 0x18 */ u16 TexAnimNum;
  /* 0x1A */ u16 TexAnimTimer;
  /* 0x1C */ s32 ang;
  /* 0x20 */ NJS_POINT3 Up;
  /* 0x2C */ NJS_POINT3 Pos;
  /* 0x38 */ AL_ICON_INFO Upper;
  /* 0x7C */ AL_ICON_INFO Lower;
} AL_ICON; // size: 0xC0

typedef struct {
  /* 0x0 */ u16 Flag;
  /* 0x2 */ u16 CurrNum;
  /* 0x4 */ f32 Ratio;
  /* 0x8 */ NJS_LINE Plane;
} AL_ZONE; // size: 0x20

struct al_perception_link {
  /* 0x00 */ s16 info[4];
  /* 0x08 */ f32 tgtdist;
  /* 0x0C */ s32 InSightFlag;
  /* 0x10 */ s32 HearFlag;
  /* 0x14 */ s32 SmellFlag;
  /* 0x18 */ ALW_ENTRY_WORK *pEntry;
}; // size: 0x1C

typedef struct al_perception_link AL_PERCEPTION_LIST[32];

typedef struct {
  /* 0x00 */ u16 nbPerception;
  /* 0x04 */ s32 InSightFlag;
  /* 0x08 */ s32 HeardFlag;
  /* 0x0C */ s32 SmellFlag;
  /* 0x10 */ f32 NearestDist;
  /* 0x14 */ s16 NearestNum;
  /* 0x18 */ AL_PERCEPTION_LIST list;
} AL_PERCEPTION_INFO; // size: 0x398

typedef struct {
  /* 0x0000 */ f32 SightRange;
  /* 0x0004 */ s32 SightAngle;
  /* 0x0008 */ s32 SightAngleHalf;
  /* 0x000C */ f32 HearRange;
  /* 0x0010 */ f32 SmellRange;
  /* 0x0014 */ AL_PERCEPTION_INFO Player;
  /* 0x03AC */ AL_PERCEPTION_INFO Chao;
  /* 0x0744 */ AL_PERCEPTION_INFO Fruit;
  /* 0x0ADC */ AL_PERCEPTION_INFO Tree;
  /* 0x0E74 */ AL_PERCEPTION_INFO Toy;
  /* 0x120C */ AL_PERCEPTION_INFO Sound;
} AL_PERCEPTION; // size:0x15A4

#define GET_CHAOWK(_tp)     ((chaowk*)(_tp)->twp)

typedef struct chaowk {
  TASKWK;

  /* 0x0030 */ u32 Timer;
  /* 0x0034 */ task *pMayu;
  /* 0x0038 */ task *pBooktask;
  /* 0x003C */ s32 NestFlag;
  /* 0x0040 */ task *pAnytask;
  /* 0x0044 */ task *pAimtask;
  /* 0x0048 */ s32 AimNum;
  /* 0x004C */ s32 RememberNum;
  /* 0x0050 */ s32 pitch;
  /* 0x0054 */ f32 ClimbFirstPos;
  /* 0x0058 */ BOOL IsParamCopy;
  /* 0x005C */ CHAO_PARAM_GC *pParamGC;
  /* 0x0060 */ TMP_PARAM tmpParam;
  /* 0x0088 */ s32 Stamina;
  /* 0x008C */ s32 AimStamina;
  /* 0x0090 */ task *tp;
  /* 0x0094 */ Angle pre_ang[3];
  /* 0x00A0 */ u32 ChaoFlag;
  /* 0x00A4 */ u16 ColliFormat;
  /* 0x00A8 */ f32 CurrZone;
  /* 0x00AC */ MOTION_CTRL MotionCtrl;
  /* 0x00F8 */ MOTION_CTRL MiniMotionCtrl;
  /* 0x0144 */ MOTION_TABLE MiniMotionTable[4];
  /* 0x01b4 */ AL_BEHAVIOR Behavior;
  /* 0x0510 */ AL_SHAPE Shape;
  /* 0x068C */ AL_FACE_CTRL Face;
  /* 0x06EC */ AL_ICON Icon;
  /* 0x07AC */ AL_ZONE Zone;
  /* 0x07CC */ AL_PERCEPTION Perception;
  /* 0x1D70 */ void *pWork;
} chaowk; // size: 0x1D74

typedef struct al_shape_element {
  /* 0x00 */ u8 type;
  /* 0x01 */ u8 DefaultEyeNum;
  /* 0x02 */ u8 DefaultMouthNum;
  /* 0x03 */ u8 HonbuNum;
  /* 0x04 */ u8 ObakeHead;
  /* 0x05 */ u8 ObakeBody;
  /* 0x06 */ u8 MedalNum;
  /* 0x07 */ u8 ColorNum;
  /* 0x08 */ u8 NonTex;
  /* 0x09 */ u8 JewelNum;
  /* 0x0A */ u8 MultiNum;
  /* 0x0B */ s8 MinimalParts[8];
  /* 0x14 */ s16 HPos;                // divided by 10'000 on copy
  /* 0x16 */ s16 VPos;                // divided by 10'000 on copy
  /* 0x18 */ s16 APos;                // divided by 10'000 on copy
  /* 0x1A */ s16 Growth;              // divided by 10'000 on copy
  /* 0x1C */ u8 name[8];
  /* 0x24 */ u16 Skill[8];
} AL_SHAPE_ELEMENT; // size: 0x34

/************************/
/*  Data                */
/************************/
/** Collision info **/
#define colli_info_chao     DATA_ARY(CCL_INFO, 0x013134D0, [5])

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** 'pParamGC' can be NULL, and a new paramGC will be generated
    'IsParamCopy' copies given 'pParamGC' info and doesn't add it to the ALW entry save info
    'pElement' can be NULL, moves it's info into Chao's paramGC **/
task*   CreateChaoExtra(CHAO_PARAM_GC* pParamGC, BOOL IsParamCopy, AL_SHAPE_ELEMENT* pElement, NJS_POINT3* pPos, Angle angy);

/** Task functions **/
void    ChaoExecutor(task* tp);
void    ChaoDestructor(task* tp);
void    ChaoDisplayer(task* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define CreateChaoExtra_p        FUNC_PTR(task*, __cdecl, (CHAO_PARAM_GC*, BOOL, AL_SHAPE_ELEMENT*, NJS_POINT3*, Angle), 0x005501D0)
#   define ChaoExecutor_p           FUNC_PTR(void , __cdecl, (task*)                                                     , 0x0054FE20)
#   define ChaoDestructor_p         FUNC_PTR(void , __cdecl, (task*)                                                     , 0x0054FF30)
#   define ChaoDisplayer_p          FUNC_PTR(void , __cdecl, (task*)                                                     , 0x0054FF80)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_CHAO_H_*/
