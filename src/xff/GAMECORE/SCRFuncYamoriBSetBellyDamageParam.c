extern void *GetSCRCharaAIWorkPtr();

void SCRFuncYamoriBSetBellyDamageParam(float fparg0)
{
    (*(float *)((char *)(GetSCRCharaAIWorkPtr()) + 0x41E8)) = fparg0;
}
