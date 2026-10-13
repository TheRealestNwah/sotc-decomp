extern void *GetSCRCharaAIWorkPtr();

void SCRFuncMinoCAtkCountInit(void)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41E8)) = 0;
}
