extern char gcGlobalVar[];
extern char *GetSCRCharaAIWorkPtr(void *);
extern char *getSCRDataCtrlWork(void *);
extern void *getPlayerColCont2(int);
extern int ColCont2_IsColStatus(void *, long, long);

void SCRFuncUnageMainBossNotParentTime(void *a)
{
    char *w = GetSCRCharaAIWorkPtr(a);
    if (ColCont2_IsColStatus(getPlayerColCont2(*(int *)(getSCRDataCtrlWork(a) + 0x4078)), 1, 1))
        *(float *)(w + 0x5B30) = 0.0f;
    else
        *(float *)(w + 0x5B30) += *(float *)(gcGlobalVar + 0x180);
}
