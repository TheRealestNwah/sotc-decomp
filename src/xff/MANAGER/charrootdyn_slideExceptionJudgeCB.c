#ifdef NONMATCHING /* Parked: 6 words differ (the "p[0] != 0" test falls through to return 1 instead of
   branching likely to the exit and jumping to the final mask test). Empty asm barriers keep the
   compare constants inside each branch; tried result variable, gotos, __builtin_expect. */
extern unsigned long *GetCollisionDBAttributeAdr(void *);

int charrootdyn_slideExceptionJudgeCB(void *gp, int *p)
{
    unsigned long attr = *GetCollisionDBAttributeAdr(gp);
    unsigned long lo = attr & 0x7C000000;
    unsigned long hi = attr & 0xF80000000;

    if (p != 0) {
        if (p[1] == 0) {
            __asm__ __volatile__("");
            if (hi == 0x480000000)
                return 0;
        }
        if (p[0] != 0)
            return 1;
    } else {
        __asm__ __volatile__("");
        if (hi == 0x480000000)
            return 0;
    }
    if (lo == 0x14000000) {
        __asm__ __volatile__("");
        return 0;
    }
    return 1;
}
#endif
