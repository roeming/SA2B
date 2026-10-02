#include "sa2b_types.h"
#include "samt/sonic/task.h"

// 0x822D48E8	procedure	173
void SetObject(task *pTask);
// 0x822D45E0	procedure	250
void InitStatusTable();
// 0x822D38E0	procedure	307
Sint32 CheckRangeP2XYZRP(Float *pf, Float rx0, Float ry0, Float rz0, Float R,
                         Float *pf2);
// 0x822D3980	procedure	423
void ProcessStatusTable2P();
// 0x822D3C80	procedure	596
void ProcessStatusTable1P();
// 0x822D4720	procedure	822
void SwitchStatusTable(taskwk *pTaskWork);
// 0x822D3FF8	procedure	902
void SetStatusEntry();
// 0x822D4118	procedure	1012
void ReleaseStatusEntry();
// 0x822D4200	procedure	1074
void ReviveSetObject();
// 0x822D4280	procedure	1131
void AddSetStage(Sint16 ssGap);
// 0x822D4880	procedure	1156
Sint32 CheckRange(task *pTask);	
// 0x822D42E0	procedure	1187
Sint32 CheckRangeWithR(task *pTask, Float fRange);
// 0x822D48A0	procedure	1227
Sint32 CheckRangeOut(task *pTask);
// 0x822D48C0	procedure	1255
Sint32 CheckRangeOut_L(task *pTask);
// 0x822D4360	procedure	1276
Sint32 CheckRangeOutWithR(task *tp, Float fRange);
// 0x822D44C0	procedure	1386
void SetBroken(task *pTask);
// 0x822D44D8	procedure	1406
void SetNoRevive(task *pTask);
// 0x822D44F0	procedure	1426
Sint32 CheckBroken(task *pTask);
// 0x822D4500	procedure	1444
void SetContinue(task *pTask);
// 0x822D4518	procedure	1482
void Dead(task *pTask); 
// 0x822D4540	procedure	1503
void DeadOut(task *pTask);
// 0x822D4578	procedure	1553
void SetUserFlag(task *tp, Sint8 flag);
// 0x822D4590	procedure	1571
Sint8 GetUserFlag(task *tp);
// 0x822D45B0	procedure	1586
void SetObjEditTable(void *pTable);

BOOL _rename_CheckFlag0x20(task*);
void _rename_SetFlag0x20(task*);
BOOL _rename_CheckFlag0x40(task*);
void _rename_SetFlag0x40(task*);
// data
// Sint32 boolCheckRangeIn	0x8316BF44	data
// Sint32 boolOneShot	0x85C2AFAC	data
// Sint32 boolStageAdvanced	0x85C2AFA8	data
// unsigned Sint32 IsRecCondObj[1]	0x8316BF48	data
