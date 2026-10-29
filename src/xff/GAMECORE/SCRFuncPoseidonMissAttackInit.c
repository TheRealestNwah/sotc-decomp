extern void *GetSCRCharaAIWorkPtr(void *);
void SCRFuncPoseidonMissAttackInit(void *actor, int value)
{
    *(int *)((char *)GetSCRCharaAIWorkPtr(actor) + 0x41C4) = value;
}
