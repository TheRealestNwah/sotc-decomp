extern int DldSysUndefSymbol;
extern void _SCRStartLWS(int, int, int, int);
extern void setGameFlagForGameObj(int);

void SCRFuncStartGameObjectLWS(void *a, int lws, int flag, int d, int e, int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    int *g = (t != 0 && t != (int *)DldSysUndefSymbol) ? (int *)t[4] : 0;
    if (g != 0 && g[2] != 0) {
        _SCRStartLWS(g[2], -1, lws, 0);
        if (flag != 0) {
            setGameFlagForGameObj(g[2]);
            g = 0;
        }
    }
}
