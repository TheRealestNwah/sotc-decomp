extern void *GetSCRCharaAIWorkPtr(void *);
void SCRFuncNargaSetPlayerDamage(void *actor, int value)
{
    *(int *)((char *)GetSCRCharaAIWorkPtr(actor) + 0x5AA4) = value;
}
