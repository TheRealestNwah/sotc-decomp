extern void *GetSCRCharaAIWorkPtr();

void SCRFuncPoseidonAngryCountInit(void)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41D0)) = 0;
}
