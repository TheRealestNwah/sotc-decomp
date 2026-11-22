extern int *DldSysUndefSymbol;
static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != DldSysUndefSymbol)
        return (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3];
    return 0;
}

extern void *GetCharacterClass(void *);
extern void setRatioGazeIKWork(void *, float, float, float);
extern void setGoingAngleGazeIKWork(void *, float);
extern void setSubParamGazeIKWork(void *, void *);
extern void setExecRootQuatGazeIKWork(void *, int);
extern void setExecGazeCtrlWork(void *, int);
extern void setNextDistGazeCtrlWork(void *, float);
extern void setViewJudgeGazeCtrlWork(void *, int);
extern void setGazeCoffGazeCtrlWork(void *, float);
extern void setValidPosGazeCtrlWork(void *, int);
extern void setObjGazeCtrlWork(void *, int);
extern void setBirdModeGazeCtrlWork(void *, int);

void setSCRGazeStatus(void *obj, char *w, unsigned int *h)
{
    char *s = dldResolve(h);
    char *g = w + 0x3CC0;

    if (s == 0)
        return;
    setRatioGazeIKWork(GetCharacterClass(obj), *(float *)(s + 0x20), *(float *)(s + 0x18), *(float *)(s + 0x1C));
    setGoingAngleGazeIKWork(GetCharacterClass(obj), *(float *)(s + 4));
    setSubParamGazeIKWork(GetCharacterClass(obj), dldResolve((unsigned int *)(s + 0x28)));
    setExecRootQuatGazeIKWork(GetCharacterClass(obj), *(int *)(s + 0x14));
    setExecGazeCtrlWork(g, *(int *)s);
    setNextDistGazeCtrlWork(g, *(float *)(s + 8));
    setViewJudgeGazeCtrlWork(g, *(int *)(s + 0x10));
    setGazeCoffGazeCtrlWork(g, *(float *)(s + 0x24));
    switch (*(int *)(s + 0xC)) {
    case 0:
        setValidPosGazeCtrlWork(g, 0);
        setObjGazeCtrlWork(g, 0);
        setBirdModeGazeCtrlWork(g, 0);
        return;
    case 1:
        setValidPosGazeCtrlWork(g, 1);
        setObjGazeCtrlWork(g, *(int *)(w + 0x4078));
        setBirdModeGazeCtrlWork(g, 0);
        return;
    case 2:
        setValidPosGazeCtrlWork(g, 0);
        setObjGazeCtrlWork(g, 0);
        setBirdModeGazeCtrlWork(g, 1);
        return;
    case 3:
    case 4:
        setValidPosGazeCtrlWork(g, 1);
        setObjGazeCtrlWork(g, 0);
        setBirdModeGazeCtrlWork(g, 0);
        break;
    }
}
