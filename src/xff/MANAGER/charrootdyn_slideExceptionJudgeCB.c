#ifdef NONMATCHING /* near-miss: register allocation / scheduling differences remain */
extern unsigned long *GetCollisionDBAttributeAdr(void *);

int charrootdyn_slideExceptionJudgeCB(void *gp, int *p)
{
    unsigned long attr = *GetCollisionDBAttributeAdr(gp);
    unsigned long hi = attr & 0xF80000000;
    unsigned long lo = attr & 0x7C000000;

    if ((p == 0 || p[1] == 0) && hi == 0x480000000)
        return 0;
    if (p != 0 && p[0] != 0)
        return 1;
    return lo != 0x14000000;
}
#endif
