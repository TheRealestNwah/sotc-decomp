extern int DldSysUndefSymbol;
extern char SH_AdpcmSeqDEFAULT[];
extern int D_00139C68[];
extern char *D_00139C00;
extern void createParamMenu(void *, int);

static void func_000DCA70(void *a0, void *a1, int *idx)
{
    char *t;

    if (D_00139C68[12] == 0) {
        t = SH_AdpcmSeqDEFAULT != (char *)DldSysUndefSymbol ? SH_AdpcmSeqDEFAULT : 0;
        D_00139C00 = *(char **)(t + 0x10);
        D_00139C00 += *idx * 56;
        createParamMenu(D_00139C68, 0);
    }
}
