extern void *GetSCRCharaAIWorkPtr(void *);

void *SCRGetBossWork(void *actor)
{
    return *(void **)GetSCRCharaAIWorkPtr(actor);
}
