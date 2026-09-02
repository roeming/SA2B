#include "sa2b_types.h"
#include "samt/sonic/chao/al_gene.h"
#include "samt/sonic/chao/al_chao_info.h"
#include "samt/sonic/task.h"

void AL_GeneCreatePlane(AL_GENE *pGene);

void AL_GeneCreate(AL_GENE *pGene);

void AL_GeneCreateGBA(AL_GENE *pGene, CHAO_PARAM_GC *pParam);

void AL_GeneCreateGBAEgg(AL_GENE *pGene, CHAO_PARAM_GC *pParam);

void AL_GeneCreate_Light(AL_GENE *pGene);

void AL_GeneCreate_Dark(AL_GENE *pGene);

void AL_EmotionStateInit(AL_EMOTION*);

void AL_SucceedGeneParam(AL_GENE *pGene, CHAO_PARAM_GC *pParam);

void AL_AblLevelUp(int skill, AL_GENE *pGene, CHAO_PARAM_GC *pParam);

void AL_GrowGeneParam(AL_GENE *pGene, CHAO_PARAM_GC *pParam);

void AL_BlendGene(AL_GENE *pSrcGene1, AL_GENE *pSrcGene2, AL_GENE *pDstGene);

void AL_CreateChildGene(task *pMotherTask, task *pFatherTask, AL_GENE *pChildGene);

void AL_GeneAnalyzeCommon(AL_GENE *pGene, CHAO_PARAM_GC *pParam);

void AL_GeneAnalyze2(AL_GENE *pGene, CHAO_PARAM_GC *pParam);

void AL_GeneAnalyze(task *tp);
