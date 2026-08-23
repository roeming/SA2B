/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/task/taskwk.h'
*
*   Description:
*     Task 'Task Work'.
*/
#ifndef H_SA2B_TASK_TASKWK
#define H_SA2B_TASK_TASKWK

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** Colliwk *********************************************************************************/
typedef struct colliwk              colliwk; /* collision work                                  */

/********************************/
/*  Structures                  */
/********************************/
/****** Work Macro ******************************************************************************/
#define TASKWK struct { \
    s8          mode;               /* 0x00 task mode                                                */ \
    s8          smode;              /* 0x01 task secondary mode                                      */ \
    u8          id;                 /* 0x02 task id                                                  */ \
    u8          btimer;             /* 0x03 byte timer                                               */ \
    s16         flag;               /* 0x04 task flags                                               */ \
    u16         wtimer;             /* 0x06 word timer                                               */ \
    Angle3      ang;                /* 0x08 task angle                                               */ \
    NJS_POINT3  pos;                /* 0x14 task position                                            */ \
    NJS_VECTOR  scl;                /* 0x20 task scale                                               */ \
    colliwk*    cwp;                /* 0x2C collision work pointer                                   */ \
}

/****** Work ************************************************************************************/
#define TO_TASKWK(p)                ((taskwk*)(p))

typedef struct taskwk
{
    TASKWK;                         /* task work                                                */
}
taskwk;

EXTERN_END

#endif/*H_SA2B_TASK_TASKWK*/
