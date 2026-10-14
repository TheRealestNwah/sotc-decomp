extern void *GetSCRCharaAIWorkPtr(void *);

float SCRGetBossWeakPointAngleFromIndex(void *actor, int index)
{
    void *boss;
    char *points;

    boss = *(void **)GetSCRCharaAIWorkPtr(actor);
    points = *(char **)((char *)boss + 0x10);
    return *(float *)(points + index * 0x58 + 0x30);
}
