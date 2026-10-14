extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncMinoCTargetWallReset(void *actor)
{
    (*(int *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41F8)) = 0;
}
