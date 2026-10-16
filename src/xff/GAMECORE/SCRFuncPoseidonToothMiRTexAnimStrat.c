extern char *GetSCRCharaAIWorkPtr(void *);
extern void bootTexAlphaAnim(void *, void *, float, float);
extern int D_0017AF40[];

static inline int texAnimEnd(unsigned int *f, unsigned int on, unsigned int end)
{
    if ((*f & end) != end) {
        if ((*f & on) == on)
            *f ^= on;
        *f |= end;
        return 1;
    }
    return 0;
}

void SCRFuncPoseidonToothMiRTexAnimStrat(void *a)
{
    if (texAnimEnd((unsigned int *)(GetSCRCharaAIWorkPtr(a) + 0x41D4), 8, 4))
        bootTexAlphaAnim(a, D_0017AF40, 1.0f, 0.05f);
}
