extern char *GetSCRCharaAIWorkPtr(void *);
extern void bootTexAlphaAnim(void *, void *, float, float);
extern int D_0017AF28[];

static inline int texAnimEnd(unsigned int *f, unsigned int on, unsigned int end)
{
    if (!(*f & end)) {
        if ((*f & on) == on)
            *f ^= on;
        *f |= end;
        return 1;
    }
    return 0;
}

void SCRFuncPoseidonToothMiFTexAnimEnd(void *a)
{
    if (texAnimEnd((unsigned int *)(GetSCRCharaAIWorkPtr(a) + 0x41D4), 1, 2))
        bootTexAlphaAnim(a, D_0017AF28, 0.0f, -0.05f);
}
