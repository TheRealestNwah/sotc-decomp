extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncYamoriBUnsetRandom(void *actor)
{
    char *w = ((char *)GetSCRCharaAIWorkPtr(actor));

    *(int *)(w + 0x41D0) = 0;
    *(int *)(w + 0x41D4) = 0;
}
