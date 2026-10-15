extern char *GetSCRCharaAIWorkPtr(void *);
extern float RO_00180B68;
extern void setSelfColAndNearMinDist(char *, int, float);
extern void setPassageWideRayPathWork(char *, int);
extern void setReductionCosUserPathWork(char *, float);
extern void setObstacleWormCtrlWork(char *, int);

void SCRFuncUnagiResetSelfColiForPath(void *a)
{
    char *w = GetSCRCharaAIWorkPtr(a);
    setSelfColAndNearMinDist(w + 0x10, 0, RO_00180B68);
    setPassageWideRayPathWork(w + 0x10, 0);
    setReductionCosUserPathWork(w + 0x10, 3.1415926f);
    setObstacleWormCtrlWork(w + 0x3D20, 0);
}
