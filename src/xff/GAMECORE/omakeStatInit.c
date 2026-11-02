typedef struct {
    long long q[14];
} OmakeStat;

extern OmakeStat B_00184778;
extern void *memset(void *, int, unsigned int);
extern void _omakeSelectFlagSet(int);

static inline void statSelectFlagSet(char *stat, int i)
{
    stat[2 + i / 8] |= 1 << (i & 7);
    _omakeSelectFlagSet(i);
}

void omakeStatInit(int flag, OmakeStat *src, int arg)
{
    char *stat;

    if (src == 0) {
        stat = (char *)&B_00184778;
        memset(stat, 0, sizeof(OmakeStat));
        statSelectFlagSet(stat, 15);
        statSelectFlagSet(stat, 21);
        statSelectFlagSet(stat, 17);
        *(int *)(stat + 0x24) = arg;
        if (flag != 0) {
            *(int *)(stat + 0x20) = 1;
            statSelectFlagSet(stat, 10);
        }
    } else {
        B_00184778 = *src;
    }
}
