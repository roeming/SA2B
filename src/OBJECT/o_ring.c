#include "OBJECT/o_ring.h"
#include "set.h"

void o_ring_1(){

}

void Ring(task* tp)
{
    
}

void o_ring_3() {}

void o_ring_4() {}

int o_ring_5(NJS_VECTOR* p) {
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

void Tobitiri() {}

void o_ring_7() {}

void o_ring_8() {}

void o_ring_9() {}

void o_ring_10() {}

void o_ring_11() {}

void RingModelExec() {}

void o_ring_13() {}

void o_ring_14() {}

void o_ring_15() {}

void o_ring_16(task* tp) {
    if (CheckRangeOut(tp)){
        return;
    }
}
