extern void *DldSysUndefSymbol;
extern char SH_AdpcmSeqDEFAULT[];
extern int D_00139E08;
extern char B_0014E898[];
extern char D_00139DD8[];
extern void func_000DCCA8(void);
extern int _adpcmOpenReq(void *, int, void (*)(void), int);
extern void createMenu(void *, int);

static void T_000DCB48(void *a, void *b, int *sel)
{
    char *m = DldSysUndefSymbol == SH_AdpcmSeqDEFAULT ? 0 : SH_AdpcmSeqDEFAULT;
    char *seq = *(char **)(m + 0x10) + *sel * 56;
    int cur = D_00139E08;

    if (cur >= 0) {
        char *e;

        D_00139E08 = -1;
        e = B_0014E898 + cur * 0x560;
        *(unsigned long *)(e + 0x38) |= 0x2000000000UL;
        *(int *)(e + 0x44) = 0;
    }
    D_00139E08 = _adpcmOpenReq(seq, 1, func_000DCCA8, 0);
    createMenu(D_00139DD8, 0);
}
