extern char *GetSCRCharaAIWorkPtr();

void SCRFuncYamoriBUnsetRandom(void)
{
    char *w = GetSCRCharaAIWorkPtr();

    *(int *)(w + 0x41D0) = 0;
    *(int *)(w + 0x41D4) = 0;
}
