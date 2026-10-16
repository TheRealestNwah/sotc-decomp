extern char *GetSCRCharaAIWorkPtr(void *);
extern void func_000D1A80(void *, void *, int, int);
extern int memcmp(const void *, const void *, unsigned int);

int SCRConditionYamoriBChangeAttainPointForAttack(void *actor, int a1, int point)
{
    float pos[4] __attribute__((aligned(16)));
    char *work;

    work = GetSCRCharaAIWorkPtr(actor);
    func_000D1A80(actor, pos, 1, point);
    return memcmp(pos, work + 0x41F0, 16) != 0;
}
