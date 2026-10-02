/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/task.h'
*
*   Description:
*     SA2's game object system.
*/
#ifndef H_SA2B_TASK
#define H_SA2B_TASK

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

/****** Task ************************************************************************************/
#include <samt/sonic/task/taskwk.h>   /* task work                                              */
#include <samt/sonic/task/motionwk.h> /* motion work                                            */
#include <samt/sonic/task/forcewk.h>  /* motion work                                            */
#include <samt/sonic/task/anywk.h>    /* any work                                               */
#include <samt/sonic/task/taskexec.h> /* task executor                                          */

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** Set Condition ***************************************************************************/
typedef struct _OBJ_CONDITION       OBJ_CONDITION;

/********************************/
/*  Constants                   */
/********************************/
/****** Task Flags ******************************************************************************/
#define IM_NONE                     (0)     /* no work                                          */
#define IM_MWK                      (1<<0)  /* motion work                                      */
#define IM_TWK                      (1<<1)  /* task work                                        */
#define IM_FWK                      (1<<2)  /* force work                                       */
#define IM_AWK                      (1<<3)  /* any work                                         */

/********************************/
/*  Enums                       */
/********************************/
/****** Task Level ******************************************************************************/
typedef enum
{
    LEV_0,                          /* level 0, high priority                                   */
    LEV_1,                          /* level 1, high priority                                   */
    LEV_2,                          /* level 2                                                  */
    LEV_3,                          /* level 3                                                  */
    LEV_4,                          /* level 4                                                  */
    LEV_5,                          /* level 5                                                  */
    LEV_6,                          /* level 6                                                  */
    LEV_C,                          /* create only, task not added to btp list                  */

    LEV_M                           /* task level max                                           */
}
tasklevel;

/********************************/
/*  Structures                  */
/********************************/
/****** Task ************************************************************************************/
typedef struct task
{
    struct task*    next;           /* 0x0 next                                                     */
    struct task*    last;           /* 0x4 last                                                     */
    struct task*    ptp;            /* 0x8 parent                                                   */
    struct task*    ctp;            /* 0xC child                                                    */

    task_exec       exec;           /* 0x10 executor                                                 */
    task_exec       disp;           /* 0x14 displayer                                          [1st] */
    task_exec       dest;           /* 0x18 destructor                                               */
    task_exec       disp_dely;      /* 0x1C delayed displayer                                  [3rd] */
    task_exec       disp_sort;      /* 0x20 sorted displayer                                   [2nd] */
    task_exec       disp_late;      /* 0x24 late displayer                                     [4th] */
    task_exec       disp_last;      /* 0x28 last displayer                                     [5th] */
    task_exec       disp_shad;      /* 0x2C shadow displayer                                         */

    OBJ_CONDITION*  ocp;            /* 0x30 object/set data                                          */

    struct taskwk*   twp;           /* 0x34 task work                                                */
    struct motionwk* mwp;           /* 0x38 motion work                                              */
    struct forcewk*  fwp;           /* 0x3C force work                                  [array of 2] */
    struct anywk*    awp;           /* 0x40 any work                                                 */

    char*            name;          /* 0x44 name                                                     */
    u32              id;            /* 0x48 id                                 [unused & unfinished] */

    union {
        s8      b[4];               /* bytes                                                    */
        s16     w[2];               /* words                                                    */
        s32     l;                  /* long                                                     */
        f32     f;                  /* real                                                     */
        void*   ptr;                /* pointer                                                  */
    }
    work;                           /* 0x4C inline work                                              */
}
task;

/********************************/
/*  Variables                   */
/********************************/
/****** Task List *******************************************************************************/
#define btp                         DATA_ARY(task*    , 0x01A5A254, [LEV_M])

/********************************/
/*  Prototypes                  */
/********************************/
/****** Create Task *****************************************************************************/
/*
*   Description:
*     Create a new task.
*
*   Notes:
*     - 'Elemental' means 'foundational', as in 'not a child task'.
*
*   Parameters:
*     - im          : init mask                                                          [IM_#]
*     - level       : task level
*     - exec        : task executor                                               [opt:nullptr]
*     - name        : task name
*/
task*   CreateElementalTask( u16 im, tasklevel level, task_exec exec, const char* name );
#define CreateFundamentalTask(im, level, exec) CreateElementalTask((im), (level), (exec), #exec)
/*
*   Description:
*     Create a new task as a child of another task.
*
*   Parameters:
*     - im          : init mask                                                          [IM_#]
*     - exec        : task executor
*     - tp          : task parent
*/
task*   CreateChildTask( u16 im, task_exec exec, task* tp );

/****** Free Task *******************************************************************************/
/*
*   Description:
*     Queue a task for freeing.
*
*   Notes:
*     - Members 'ocp', 'twp', 'mwp', 'fwp', & 'awp' are freed automatically.
*
*   Parameters:
*     - tp          : task
*/
void    FreeTask( task* tp );
/*
*   Description:
*     Queue all tasks for freeing, except 'LEV_0' and 'LEV_1'.
*/
void    PurgeTask( void );
/*
*   Description:
*     Queue all tasks for freeing.
*/
void    GenocideTask( void );

/****** Destroy Task ****************************************************************************/
/*
*   Description:
*     Frees all task data, and task pointers.
*
*   Parameters:
*     - tp          : task
*/
void    DestroyTask( task* tp );

void FreeTaskC(task *tp);

#ifdef SAMT_INCL_FUNCPTRS

/********************************/
/*  Function Pointers           */
/********************************/
/****** Function Pointers ***********************************************************************/
#define CreateChildTask_p                   FUNC_PTR(task*, __cdecl, (u16, task_exec, task*), 0x00470C00)
#define PurgeTask_p                         FUNC_PTR(void , __cdecl, (void)                 , 0x00470AE0)
#define GenocideTask_p                      FUNC_PTR(void , __cdecl, (void)                 , 0x00470B10)
#define DestroyTask_p                       FUNC_PTR(void , __cdecl, (task*)                , 0x0046F720)

/****** Usercall Pointers ***********************************************************************/
#define CreateElementalTask_p               0x0046F610 /* EAX(STK,ECX,EDI,EAX) */

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_TASK*/
