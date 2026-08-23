/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/c_colli/ccl_info.h'
*
*   Description:
*       Definition for the CCL_INFO struct type.
*/
#ifndef _SA2B_CCOLLI_INFO_H_
#define _SA2B_CCOLLI_INFO_H_

/************************/
/*  Includes            */
/************************/
#include <samt/ninja/njcommon.h>

/************************/
/*  Structures          */
/************************/
typedef struct
{
    /*0x00*/ Sint8      kind;
    /*0x01*/ Uint8      form;
    /*0x02*/ Sint8      push;
    /*0x03*/ Sint8      damage;
    /*0x04*/ Uint32     attr;
    /*0x08*/ NJS_POINT3 center;
    /*0x14*/ Float        a;
    /*0x18*/ Float        b;
    /*0x1C*/ Float        c;
    /*0x20*/ Float        d;
    /*0x24*/ Sint32       angx;
    /*0x28*/ Sint32       angy;
    /*0x2C*/ Sint32       angz;
}
CCL_INFO; // size: 0x30

#endif/*_SA2B_CCOLLI_INFO_H_*/
