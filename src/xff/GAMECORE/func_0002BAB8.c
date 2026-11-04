extern int *DldSysUndefSymbol;
extern char SH_StageDataDEFAULT[];
extern char *D_0017A868;
extern int D_0017A86C;
extern int D_0017A870;
extern int D_0017A874;
extern int D_0017A878;
extern int D_0017A87C;
extern void ResetCamFinalizer(void);
extern void func_0002B838(void);
extern void scrRun(void);
extern void sheetMgrAllReqWait(int *);

void func_0002BAB8(int idx, int arg)
{
    int status;
    char *stages;
    char *entry;
    unsigned int *h;
    int off;
    int *sym;
    int *area;
    char **stage = &D_0017A868;

    D_0017A870 = 0;
    ResetCamFinalizer();
    if (*stage != 0)
        func_0002B838();
    *stage = 0;
    D_0017A86C = 0;
    if (idx >= 0) {
        stages = SH_StageDataDEFAULT != (char *)DldSysUndefSymbol ? SH_StageDataDEFAULT : 0;
        entry = stages != 0 ? *(char **)(stages + 0x10) + idx * 20 : 0;
        h = (unsigned int *)(entry + 8);
        off = *h & 0x3FFFF;
        sym = off != 0 ? *(int **)((char *)h - off) : 0;
        *stage = (sym != 0 && sym != DldSysUndefSymbol) ? (char *)sym[4] : 0;
        if (D_0017A868 != 0) {
            area = &D_0017A86C;
            h = (unsigned int *)(D_0017A868 + 0x30);
            off = *h & 0x3FFFF;
            sym = off != 0 ? *(int **)((char *)h - off) : 0;
            *area = (sym != 0 && sym != DldSysUndefSymbol) ? sym[4] : 0;
        }
    }
    D_0017A878 = 0;
    D_0017A874 = arg;
    D_0017A87C = arg;
    D_0017A870 = 1;
    status = 0;
    scrRun();
    sheetMgrAllReqWait(&status);
    while ((unsigned int)(status - 0xDEAF) >= 2)
        scrRun();
}
