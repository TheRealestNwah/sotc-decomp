extern int DldSysUndefSymbol;
extern char SH_AdpcmSeqDEFAULT[];
extern int D_00139BF4;
extern int D_00139E10[];
extern void createSheetMenu(void *, int);

void createAdpcmTest(void)
{
    char *s;
    D_00139BF4 = 1;
    s = (char *)DldSysUndefSymbol != SH_AdpcmSeqDEFAULT ? SH_AdpcmSeqDEFAULT : 0;
    D_00139E10[2] = *(int *)(s + 0x10);
    D_00139E10[3] = *(int *)(s + 0xC);
    createSheetMenu(D_00139E10, 0);
}
