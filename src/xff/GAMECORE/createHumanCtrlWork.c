extern int *DldSysUndefSymbol;
extern void setAttainRadPathWork(void *, float);
extern void func_0010B680(void *, void *);
extern void _setStopCtrlModeBaseMoveWork(void *, void *);

static inline int *dldData(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (int *)t[4] : 0;
}

static inline char *dldResolveRe(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((*h >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

void createHumanCtrlWork(void *w, char *ctrl, unsigned int *h, void *path)
{
    float *o = (float *)dldData(h);

    setAttainRadPathWork(path, 3.1415926f);
    func_0010B680(w, ctrl);
    _setStopCtrlModeBaseMoveWork(ctrl, dldResolveRe((unsigned int *)o));
    *(float *)(ctrl + 0x34) = o[1];
}
