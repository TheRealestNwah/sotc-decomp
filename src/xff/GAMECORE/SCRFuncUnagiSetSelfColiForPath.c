extern char *GetSCRCharaAIWorkPtr(void *);
extern char *GetCharacterClass(void *);
extern void setSelfColAndNearMinDist(char *, int, float);
extern void setPassageWideRayPathWork(char *, int);
extern void setReductionCosUserPathWork(char *, float);
extern void setObstacleWormCtrlWork(char *, int);

void SCRFuncUnagiSetSelfColiForPath(void *a)
{
    char *w = GetSCRCharaAIWorkPtr(a);
    setSelfColAndNearMinDist(w + 0x10, *(int *)(GetCharacterClass(a) + 0x5B4), 30.0f);
    setPassageWideRayPathWork(w + 0x10, 1);
    setReductionCosUserPathWork(w + 0x10, 2.0943951f);
    setObstacleWormCtrlWork(w + 0x3D20, 1);
}
