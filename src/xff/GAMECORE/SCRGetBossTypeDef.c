extern int **GetSCRCharaAIWorkPtr();

int SCRGetBossTypeDef(void)
{
    int *b = *GetSCRCharaAIWorkPtr();

    if (b == 0) {
        return 0;
    }
    return *b;
}
