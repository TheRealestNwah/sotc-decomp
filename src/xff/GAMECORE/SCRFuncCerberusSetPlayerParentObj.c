extern void *GetSCRCharaAIWorkPtr();
extern void *getPlayerColCont2(int);
extern void *getSCRDataCtrlWork(int);

void SCRFuncCerberusSetPlayerParentObj(int arg0)
{
    void *temp_s1;

    temp_s1 = GetSCRCharaAIWorkPtr();
    (*(int *)((char *)(temp_s1) + 0x41C8)) = (int) (*(int *)((char *)(getPlayerColCont2((*(int *)((char *)(getSCRDataCtrlWork(arg0)) + 0x4078)))) + 0x10));
}
