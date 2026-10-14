extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncBirdInitRotMode(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41D0)) = 1;
}
