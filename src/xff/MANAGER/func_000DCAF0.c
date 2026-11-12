typedef struct { int f0, f4, f8, fC; } SheetCfg;
typedef struct { char pad[0xC]; int fC; int f10; } SheetSrc;

extern int D_00139BF4;
extern SheetCfg D_00139CA0;
extern int DldSysUndefSymbol;
extern char SH_AdpcmSeqDEFAULT[];
extern void createSheetMenu(SheetCfg *, int, SheetCfg *, int);

static void func_000DCAF0(void) {
    SheetSrc *p;
    int a3;
    register SheetCfg *c __asm__("$6") = &D_00139CA0;
    D_00139BF4 = 1;
    p = (SheetSrc *)SH_AdpcmSeqDEFAULT;
    if (p == (SheetSrc *)DldSysUndefSymbol) p = 0;
    a3 = p->f10;
    c->f8 = a3;
    c->fC = p->fC;
    createSheetMenu(c, 0, c, a3);
}
