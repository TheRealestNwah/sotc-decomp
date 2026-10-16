extern int DldSysUndefSymbol;
extern char *GetScriptAnimationClass(void *);

int SCRConditionCheckGameObjLwsPlayMode(void *a, int mode, int c, int d, int e, int f, int g, int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    int *o = (t != 0 && t != (int *)DldSysUndefSymbol) ? (int *)t[4] : 0;
    if (o != 0 && o[2] != 0)
        return mode == *(signed char *)(GetScriptAnimationClass((void *)o[2]) + 0x364);
    return 0;
}
