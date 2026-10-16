extern int DldSysUndefSymbol;
extern char *GetScriptAnimationClass(void *);
extern void _SCRStartLWS(int, int, int, int);
extern void setGameFlagForGameObj(int);

int SCRFuncStartGameObjectLWSCheckStatus(void *a, int mode, int flag, int d, int e, int *h)
{
    int ooff = *h & 0x3FFFF;
    int *ot = ooff != 0 ? *(int **)((char *)h - ooff) : 0;
    int *o = (ot != 0 && ot != (int *)DldSysUndefSymbol) ? (int *)ot[4] : 0;

    if (o != 0 && o[2] != 0) {
        if (mode != *(signed char *)(GetScriptAnimationClass((void *)o[2]) + 0x364)) {
            _SCRStartLWS(o[2], -1, mode, 0);
            if (flag)
                setGameFlagForGameObj(o[2]);
        }
    }
}
