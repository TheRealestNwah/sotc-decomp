extern char *GetSCRCharaAIWorkPtr(void *);
extern void bootTexAlphaAnim(void *, void *, float, float);
extern int D_0017AF10[];

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

void SCRFuncPoseidonToothMiLTexAnimEnd(void *a)
{
    if (texAnimEnd((unsigned int *)(GetSCRCharaAIWorkPtr(a) + 0x41D4), 0x10, 0x20))
        bootTexAlphaAnim(a, D_0017AF10, 0.0f, -0.05f);
}
