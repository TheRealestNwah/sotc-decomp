extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncYamoriBSetRandomRadius2(void *actor, float first, float second)
{
    void *work;

    work = GetSCRCharaAIWorkPtr(actor);
    *(float *)((char *)work + 0x41D8) = first;
    *(float *)((char *)work + 0x41DC) = second;
    *(volatile int *)((char *)work + 0x41D4) = 1;
    *(volatile int *)((char *)work + 0x41D0) = 1;
}
