extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncMinoCAtkCountInit(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41E8)) = 0;
}
