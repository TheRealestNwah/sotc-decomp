extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncYamoriBSetBellyDamageParam(void *actor, float fparg0)
{
    (*(float *)((char *)(GetSCRCharaAIWorkPtr(actor)) + 0x41E8)) = fparg0;
}
