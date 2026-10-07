/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/motion.h'
*
*   Contains structs and functions related to object motion data
*/
#ifndef _SA2B_MOTION_H_
#define _SA2B_MOTION_H_

/************************/
/*  Includes            */
/************************/
/****** Hook Info *******************************************************************/
#include <samt/ninja/ninja.h>

EXTERN_START

/************************/
/*  Enums               */
/************************/
/****** Hook Info *******************************************************************/
enum
{
    MD_MTN_LOOP,
    MD_MTN_ADLP,
    MD_MTN_LKLP,
    MD_MTN_STOP,
    MD_MTN_LINK,
    MD_MTN_SKIP,
    MD_MTN_CHNG,
    MD_MTN_BACK,
};

/************************/
/*  Structures          */
/************************/
/****** Hook Info *******************************************************************/
typedef struct {
  /* 0x00 */ NJS_MOTION *pMotion;
  /* 0x04 */ int16_t mode;
  /* 0x06 */ int16_t posture;
  /* 0x08 */ int32_t next;
  /* 0x0C */ int32_t link_step;
  /* 0x10 */ f32 start;
  /* 0x14 */ f32 end;
  /* 0x18 */ f32 spd;
} MOTION_TABLE; // size: 0x1C

typedef struct {
  /* 0x00 */ uint16_t mode;
  /* 0x04 */ f32 frame;
  /* 0x08 */ f32 start;
  /* 0x0C */ f32 end;
  /* 0x10 */ f32 spd;
  /* 0x14 */ NJS_MOTION *pMotion;
} MOTION_INFO; // size: 0x18

typedef struct 
{
  /* 0x00 */ uint16_t flag;
  /* 0x02 */ uint16_t posture;
  /* 0x04 */ int32_t curr_num;
  /* 0x08 */ int32_t next_num;
  /* 0x0C */ f32 multi_spd;
  /* 0x10 */ f32 link_spd;
  /* 0x14 */ f32 ratio;
  /* 0x18 */ MOTION_INFO minfo[2];
  /* 0x48 */ MOTION_TABLE *table;
} MOTION_CTRL; // size: 0x4c

/************************/
/*  Functions           */
/************************/
/****** Init Motion *****************************************************************/
/*
*   Description:
*     Init a motion control structure with a motion table
*/
void        MotionInit( MOTION_CTRL* pMtnCtrl, MOTION_TABLE* pTable );

void        MotionControl( MOTION_CTRL* pMtnCtrl );

BOOL         IsMotionEnd(  MOTION_CTRL* pMtnCtrl );
BOOL         IsMotionStop( MOTION_CTRL* pMtnCtrl );

void        SetMotionFrame( MOTION_CTRL* pMtnCtrl, f32 frame );
void        SetMotionSpd(   MOTION_CTRL* pMtnCtrl, f32 spd   );

void        SetMotionNum( MOTION_CTRL* pMtnCtrl, int32_t MtnNum );

void        SetMotionNext( MOTION_CTRL* pMtnCtrl );

s32         GetMotionNum( const MOTION_CTRL* pMtnCtrl );

f32         GetMotionFrame(   const MOTION_CTRL* pMtnCtrl );
s32         GetMotionPosture( const MOTION_CTRL* pMtnCtrl );

void        SetMotionChange( MOTION_CTRL* pMtnCtrl, int32_t MtnNum );
void        SetMotionSkip(   MOTION_CTRL* pMtnCtrl, int32_t MtnNum );

void        SetMotionLink(     MOTION_CTRL* pMtnCtrl, int32_t MtnNum );
void        SetMotionLinkSync( MOTION_CTRL* pMtnCtrl, int32_t MtnNum );
void        SetMotionLinkStep( MOTION_CTRL* pMtnCtrl, int32_t MtnNum, uint16_t step );

void        DrawMotion(  NJS_CNK_OBJECT* pObject, MOTION_CTRL* pMtnCtrl );
void        DrawGinjaMotion( GJS_OBJECT* pObject, MOTION_CTRL* pMtnCtrl );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** User-Function ptrs **/
#   define MotionInit_p             0x00793880
#   define MotionControl_p          0x007938D0
#   define SetMotionLink_p          0x00793C40
#   define SetMotionLinkStep_p      0x00793D30
#   define DrawMotion_p             0x00793F90
#   define DrawGinjaMotion_p        0x00794010

#   define SetMotionFrame_p         0x00794070

#   define IsMotionEnd_p            0x00793F70
#   define IsMotionStop_p           0x00793F80

#   define SetMotionLinkSync_p      0x00793D90

#   define SetMotionChange_p        0x00793EA0
#   define SetMotionSkip_p          0x00793E40

#   define SetMotionNext_p          0x00793CB0

#   define SetMotionNum_p           0x00793F10

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_MOTION_H_*/
