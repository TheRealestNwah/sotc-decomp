extern void *GetSCRCharaAIWorkPtr(void *);

int SCRGetBossTypeDef(void *actor)
{
    int *b = *((int **)GetSCRCharaAIWorkPtr(actor));

    if (b == 0) {
        return 0;
    }
    return *b;
}
