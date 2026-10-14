extern void *GetSCRCharaAIWorkPtr(void *);
extern void *getPlayerColCont2(void *);
extern void *getSCRDataCtrlWork(int);

void SCRFuncCerberusSetPlayerParentObj(int arg0)
{
    void *temp_s1;

    temp_s1 = GetSCRCharaAIWorkPtr((void *)arg0);
    (*(int *)((char *)(temp_s1) + 0x41C8)) = (int) (*(int *)((char *)(getPlayerColCont2((*(void **)((char *)(getSCRDataCtrlWork(arg0)) + 0x4078)))) + 0x10));
}
