extern char *GetSCRCharaAIWorkPtr(void *);
extern int T_000CBF88(void *, int, int);

int SCRConditionUnagiSelectAttackLine(void *actor, int a, int b, int c, int d, int e, int f, int g)
{
    char *w = GetSCRCharaAIWorkPtr(actor);
    *(int *)(w + 0x5ACC) = (*(int *)(w + 0x5ACC) + 1) & 0x1F;
    return T_000CBF88(actor, 1, g);
}
