typedef struct {
    char pad0[0x180];
    float unk180;
    char pad184[0x12C];
    char unk2B0[1];
} GlobalVar;

extern GlobalVar gcGlobalVar;
extern int DldSysUndefSymbol;
extern char *GetSCRCharaAIWorkPtr(void *);
extern void *SCRGetFirstObj(void *);
extern void CharaCtrlSetOutsideScriptCtrlStatus(void *, int);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

void SCRFuncFromHorceToPlayerSendKey(void *obj, int a1, int a2, int a3, int a4, int a5, int a6, int a7, unsigned int *h)
{
    char *work = GetSCRCharaAIWorkPtr(obj);
    void *player = SCRGetFirstObj(gcGlobalVar.unk2B0);
    char *key = dldResolve(h);

    if (0.0f < *(float *)(work + 0x4240)) {
        *(float *)(work + 0x4240) -= gcGlobalVar.unk180;
        if (*(float *)(work + 0x4240) < 0.0f)
            *(float *)(work + 0x4240) = 0.0f;
    }
    if (*(float *)(work + 0x4240) <= 0.0f && key != 0)
        CharaCtrlSetOutsideScriptCtrlStatus(player, *(int *)(key + 4));
}
