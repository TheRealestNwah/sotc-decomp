extern void iosGetClock(void *);
extern long iosGetClockSecond(void *);
extern void _gameWorkSet(int, int);

void setTailCutTime(void)
{
    char clk[16] __attribute__((aligned(16)));
    long t;
    int hi, lo;
    iosGetClock(clk);
    t = iosGetClockSecond(clk);
    lo = t & 0xFFFFFFFF;
    hi = t >> 32;
    _gameWorkSet(9, hi);
    _gameWorkSet(10, lo);
    t = 0;
}
