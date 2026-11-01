extern int *DldSysUndefSymbol;
extern void *getSCRDataCtrlWork(void *);
extern char *GetScriptClass(void *);
extern void setAcceleParamWormCtrlWork(void *, float, float);

static inline char *dldBase(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] : 0;
}

void SCRFuncResetAcceleParamWormCtrlParam(void *actor)
{
    void *data;
    void *work;
    char *param;

    data = getSCRDataCtrlWork(actor);
    if (*(int *)((char *)data + 0x4090) == 3) {
        work = (char *)data + 0x3D10;
        param = dldBase(*(unsigned int **)(GetScriptClass(actor) + 0x44));
        setAcceleParamWormCtrlWork(work, *(float *)(param + 0xC), *(float *)(param + 0x10));
    }
}
