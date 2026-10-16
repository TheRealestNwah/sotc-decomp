extern int DldSysUndefSymbol;
extern char *GetSCRCharaAIWorkPtr(void *);
extern void GetScriptAnimationSubObjectWithTypeFiltering(int, int, void *, void *);
extern void func_000CB3A8();

void SCRFuncTortoiseGeyserDamagedMain(void *a, int b, int c, int d, int e, int *h)
{
    char *ai = GetSCRCharaAIWorkPtr(a);
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    int *g = (t != 0 && t != (int *)DldSysUndefSymbol) ? (int *)t[4] : 0;
    *(int *)(ai + 0x41B0) = 0;
    GetScriptAnimationSubObjectWithTypeFiltering(g[2], 2, func_000CB3A8, ai);
}
