extern char *GetSCRCharaAIWorkPtr(void *);

int SCRConditionPoseidonGetPlayerTerrLog(void *a, int n)
{
    char *w = GetSCRCharaAIWorkPtr(a);
    if (n == 1)
        return *(int *)(w + 0x41CC) == 1;
    if (n == 2)
        return *(int *)(w + 0x41CC) == 2;
    return 0;
}
