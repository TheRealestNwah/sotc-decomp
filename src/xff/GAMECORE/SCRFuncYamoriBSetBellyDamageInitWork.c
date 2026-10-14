extern void *GetSCRCharaAIWorkPtr(void *);
extern const float RO_00180E94;

void SCRFuncYamoriBSetBellyDamageInitWork(void *actor)
{
    void *work;
    float initial;

    work = GetSCRCharaAIWorkPtr(actor);
    initial = RO_00180E94;
    *(int *)((char *)work + 0x41E0) = 0;
    *(float *)((char *)work + 0x41E4) = initial;
}
