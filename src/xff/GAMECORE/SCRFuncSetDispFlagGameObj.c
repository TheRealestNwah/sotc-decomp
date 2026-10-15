extern int DldSysUndefSymbol;
extern void SetLayoutObjAccessSwitch();

void SCRFuncSetDispFlagGameObj(void *a, int b, int c, int d, int e, int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    int *g = (t != 0 && t != (int *)DldSysUndefSymbol) ? (int *)t[4] : 0;
    if (g != 0 && g[2] != 0)
        SetLayoutObjAccessSwitch(g[2], b);
}
