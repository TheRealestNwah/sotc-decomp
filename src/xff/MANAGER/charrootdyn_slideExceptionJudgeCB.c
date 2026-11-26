#ifdef NONMATCHING /* Parked: 26 diffs. Testing p == 0 first gets the mask setup right; the Original keeps the
   compare constants per branch (gcc hoists 0x480000000/0x14000000 above the p test) and ends with
   a branch, not sltu. Tried: nested ifs, bitfields, result variable, laundered constants, -fno-gcse. */
extern unsigned long *GetCollisionDBAttributeAdr(void *);

int charrootdyn_slideExceptionJudgeCB(void *gp, int *p)
{
    unsigned long attr = *GetCollisionDBAttributeAdr(gp);
    unsigned long hi = attr & 0xF80000000;
    unsigned long lo = attr & 0x7C000000;

    if (p == 0) {
        if (hi == 0x480000000)
            return 0;
    } else {
        if (p[1] == 0 && hi == 0x480000000)
            return 0;
        if (p[0] != 0)
            return 1;
    }
    return lo != 0x14000000;
}
#endif
