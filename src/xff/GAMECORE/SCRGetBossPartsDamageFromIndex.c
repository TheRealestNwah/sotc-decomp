extern void *GetSCRCharaAIWorkPtr(void *);
void *SCRGetBossPartsDamageFromIndex(void *actor, int index)
{
    char *boss=*(char **)GetSCRCharaAIWorkPtr(actor);
    return *(char **)(boss + 0x10) + index * 0x58;
}
