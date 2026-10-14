extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncPoseidonMissAttackAdd(void *actor)
{
    void *temp_v0;

    temp_v0 = GetSCRCharaAIWorkPtr(actor);
    (*(int *)((char *)(temp_v0) + 0x41C4)) = (int) ((*(int *)((char *)(temp_v0) + 0x41C4)) - 1);
}
