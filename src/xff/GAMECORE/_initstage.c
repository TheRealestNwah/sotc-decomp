extern int *DldSysUndefSymbol;
extern int D_0017AF58;
extern int D_0017AF5C;
extern int D_0017AF60;
extern int D_0017AF64;
extern int D_0017AF68;
extern int D_0017AF6C;
extern char *gcGetStageData(int id);
extern void initlayout(int a0, void *a1, int a2, int a3, int t0, int t1);

void _initstage(void)
{
    unsigned int *ref;
    int off;
    int *t;
    char *p;

    ref = (unsigned int *)(gcGetStageData(D_0017AF5C) + 4);
    off = *ref & 0x3FFFF;
    t = off != 0 ? *(int **)((char *)ref - off) : 0;
    p = (t != 0 && t != DldSysUndefSymbol)
            ? (char *)t[4] + ((*ref >> 18) & 0xFFF) * ((int *)t[2])[3]
            : 0;
    initlayout(D_0017AF58, p, D_0017AF60, D_0017AF64, D_0017AF68, D_0017AF6C);
}
