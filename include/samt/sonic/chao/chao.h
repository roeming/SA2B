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
typedef struct
{
    u8  Exp[8];
    u8  Abl[8];
    u8  Lev[8];
    u16 Skills[8];
}
TMP_PARAM;

typedef struct
{
    s32 bhv;
}
KW_BHV_ENTRY;

typedef struct 
{
    u16     Flag;
    u16     Mode;
    u16     SubMode;
    u16     MoveMode;
    s32      InterruptFlag;
    s32      Timer;
    s32      SubTimer;
    s32      LimitTimer;
//  sint32       BehaviorTimer; // SADX Only
    u16     Intention;
    u16     IntentionMode;
    u16     IntentionSubMode;
    u32     IntentionTimer[18]; 
    u32     IntervalTimer[128];
    s32      FreeWork;
    f32          MoveRadius;
    NJS_POINT3   BasePos;
    BHV_FUNC     PrevFunc;
    s32      nbBhvFuncEntry;
    s32      CurrBhvFuncNum;
    BHV_FUNC     BhvFuncList[16];
    s32      ReserveTimerList[16];
    s32      CurrKwBhvNum;
    KW_BHV_ENTRY KwBhvList[4];
    u32     dummy[16];
}
AL_BEHAVIOR;

typedef struct
{
    /** Shape object **/
    AL_OBJECT* pObject;
    AL_OBJECT* CurrObjectList[40];

    /** Shape object lists **/
    AL_GROUP_OBJECT_LIST* pObjectList;
    AL_GROUP_OBJECT_LIST* pObjectListH;
    AL_GROUP_OBJECT_LIST* pObjectListD;

    /** Positions **/
    NJS_POINT3 BodyPos;
    NJS_POINT3 HeadPos;
    NJS_POINT3 LeftHandPos;
    NJS_POINT3 RightHandPos;
    NJS_POINT3 LeftFootPos;
    NJS_POINT3 RightFootPos;
    NJS_POINT3 MouthPos;

    /** Vectors **/
    NJS_VECTOR MouthVec;
    NJS_VECTOR LeftEyePos;
    NJS_VECTOR LeftEyeVec;
    NJS_VECTOR RightEyePos;
    NJS_VECTOR RightEyeVec;

    /** Left hand item **/
    NJS_CNK_OBJECT* pLeftHandItemObject;
    NJS_TEXLIST*    pLeftHandItemTexlist;
    f32             LeftHandItemScale;
    f32             LeftHandItemActiveFlag;

    /** Right hand item **/
    NJS_CNK_OBJECT* pRightHandItemObject;
    NJS_TEXLIST*    pRightHandItemTexlist;
    f32             RightHandItemScale;
    f32             RightHandItemActiveFlag;

    /** Shape info **/
    s32   palette;
    s16   Flag;
    s16   ColorNum;
    s16   EnvNum;
    s32   IconColor;
    f32       SclH;
    f32       SclV;
    f32       CamDist;
}
AL_SHAPE;

typedef struct
{
    s32    EyeTimer;
    s16    EyeColorNum;
    s16    EyeCurrNum;
    s16    EyeDefaultNum;
    s32    MouthTimer;
    s16    MouthCurrNum;
    s16    MouthDefaultNum;
    f32        EyePosX;
    f32        EyePosY;
    f32        EyeSclX;
    f32        EyeSclY;
    u32   Flag;
    AL_OBJECT* pEyeObject[2];
    AL_OBJECT* pMouthObject;
    s32    EyeLidBlinkMode;
    s32    EyeLidBlinkTimer;
    s32    EyeLidBlinkAng;
    s32    EyeLidExpressionMode;
    s32    EyeLidExpressionTimer;
    s32    EyeLidExpressionDefaultCloseAng;
    s32    EyeLidExpressionCurrCloseAng;
    s32    EyeLidExpressionAimCloseAng;
    s32    EyeLidExpressionDefaultSlopeAng;
    s32    EyeLidExpressionCurrSlopeAng;
    s32    EyeLidExpressionAimSlopeAng;
}
AL_FACE_CTRL;

typedef struct
{
    u16 Mode;
    u16 TexNum;
    u16 Timer;
    NJS_POINT3 Offset;
    NJS_POINT3 Pos;
    NJS_POINT3 Velo;
    NJS_POINT3 Scl;
    NJS_POINT3 SclSpd;
}
AL_ICON_INFO;

typedef struct
{
    s16 CurrType;
    s16 NextType;
    s32 Timer;
    s32 NextTimer;
    s32 PuniPhase;
    s32 PosPhase;
    u32 Color;
    u16 TexAnimNum;
    u16 TexAnimTimer;
    s32 ang;
    NJS_POINT3 Up;
    NJS_POINT3 Pos;
    AL_ICON_INFO Upper;
    AL_ICON_INFO Lower;
}
AL_ICON;

typedef struct
{
    u16  Flag;
    u16  CurrNum;
    f32       Ratio;
    NJS_LINE  Plane;
}
AL_ZONE;

typedef struct al_perception_link
{
    s16         info[4];
    f32             tgtdist;
    s32         InSightFlag;
    s32         HearFlag;
    s32         SmellFlag;
    ALW_ENTRY_WORK* pEntry;
}
AL_PERCEPTION_LIST[32];

typedef struct
{
    u16           nbPerception;
    s32            InSightFlag;
    s32            HeardFlag;
    s32            SmellFlag;
    f32                NearestDist;
    s16            NearestNum;
    AL_PERCEPTION_LIST list;
}
AL_PERCEPTION_INFO;

typedef struct
{
    f32                SightRange;
    s32            SightAngle;
    s32            SightAngleHalf;
    f32                HearRange;
    f32                SmellRange;
    AL_PERCEPTION_INFO Player;
    AL_PERCEPTION_INFO Chao;
    AL_PERCEPTION_INFO Fruit;
    AL_PERCEPTION_INFO Tree;
    AL_PERCEPTION_INFO Toy;
    AL_PERCEPTION_INFO Sound;
}
AL_PERCEPTION;

#define GET_CHAOWK(_tp)     ((chaowk*)(_tp)->twp)

typedef struct chaowk
{
    TASKWK;

    /* 0x30 */ u32              imer;
    /* 0x34 */ task *           pMayu;
    /* 0x38 */ task *           pBooktask;
    /* 0x3C */ s32              NestFlag;
    /* 0x40 */ task *           pAnytask;
    /* 0x44 */ task *           pAimtask;
    /* 0x48 */ s32              AimNum;
    /* 0x4C */ s32              RememberNum;
    /* 0x50 */ s32              pitch;
    /* 0x54 */ f32              ClimbFirstPos;
    /* 0x58 */ BOOL             IsParamCopy;
    /* 0x5C */ CHAO_PARAM_GC *  pParamGC;
    /* 0x60 */ TMP_PARAM        tmpParam;
    /* 0x00 */ s32              Stamina;
    /* 0x00 */ s32              AimStamina;
    /* 0x00 */ task *           tp;
    /* 0x00 */ Angle            pre_ang[3];
    /* 0x00 */ u32              ChaoFlag;
    /* 0x00 */ u16              ColliFormat;
    /* 0x00 */ f32              CurrZone;
    /* 0x00 */ MOTION_CTRL      MotionCtrl;
    /* 0x00 */ MOTION_CTRL      MiniMotionCtrl;
    /* 0x00 */ MOTION_TABLE     MiniMotionTable[4];
    /* 0x00 */ AL_BEHAVIOR      Behavior;
    /* 0x00 */ AL_SHAPE         Shape;
    /* 0x00 */ AL_FACE_CTRL     Face;
    /* 0x00 */ AL_ICON          Icon;
    /* 0x00 */ AL_ZONE          Zone;
    /* 0x00 */ AL_PERCEPTION    Perception;
    /* 0x00 */ void *           pWork;
}
chaowk;

typedef struct al_shape_element
{
    u8  type;
    u8  DefaultEyeNum;
    u8  DefaultMouthNum;
    u8  HonbuNum;
    u8  ObakeHead;
    u8  ObakeBody;
    u8  MedalNum;
    u8  ColorNum;
    u8  NonTex;
    u8  JewelNum;
    u8  MultiNum;
    s8   MinimalParts[8];
    s16  HPos;              // divided by 10'000 on copy
    s16  VPos;              // divided by 10'000 on copy
    s16  APos;              // divided by 10'000 on copy
    s16  Growth;            // divided by 10'000 on copy
    u8  name[8];
    u16 Skill[8];
}
AL_SHAPE_ELEMENT;

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
