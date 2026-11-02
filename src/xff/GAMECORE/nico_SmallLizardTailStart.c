typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

extern char rootPtn[];
extern void *isysGetThisSubThread(void);
extern int iosCreatePartition(void *, int);
extern char *GetScriptCharacterClass(void *);
extern void CharaCtrlResetCtrlStatus(void *);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern char *_SCRMallocAlign(int, int, int);
extern void isysJumpSubThread(void (*)(void), void *);
extern char *GetScriptClass(void *);
extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);
extern void *GetGeometryPointerObject(void *);
extern void SendCharaMotionSyncStartMsg(void *, void *);
extern void SCRSimpleExecCharaGeometry(void *);
extern void AI_InitAnimalWork(void *, int);
extern void AI_InitAnimalOptimize(void *);
extern int *DldSysUndefSymbol;
extern Vec4 YUnitVector;
extern void func_000B4A80(void);

static inline char *dldBase(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] : 0;
}

void nico_SmallLizardTailStart(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, 0xB3);
    char *c;
    char *w;
    char *l;
    char *cc;
    void *g;
    char *d;

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = _SCRMallocAlign(part, 0x80, 0x10);
    *(char **)(c + 0x1200) = w;
    CharaCtrlResetCtrlStatus(th);
    l = GetLayoutClass(th);
    cc = GetCharacterClass(th);
    *(int *)(w + 0x24) = 0;
    if (*(int *)(l + 0x124) != 0) {
        g = GetGeometryPointerObject(l + 0xC0);
        *(void **)(w + 0x20) = g;
        if (g != 0)
            SendCharaMotionSyncStartMsg(th, g);
        SCRSimpleExecCharaGeometry(th);
        ((Vec4 *)(w + 0x50))->q = (*(Vec4 **)(GetLayoutClass(*(void **)(w + 0x20)) + 0x134))->q;
        *(int *)(w + 0x28) = 1;
    } else {
        *(int *)(w + 0x20) = 0;
        ((Vec4 *)(w + 0x50))->q = ((Vec4 *)*(int *)(l + 0x134))->q;
        *(int *)(w + 0x28) = 0;
    }
    cc[0x536] = 0;
    AI_InitAnimalWork(w, 5);
    AI_InitAnimalOptimize(w + 0x14);
    g = GetGeometryPointerObject(GetLayoutClass(isysGetThisSubThread()) + 0xC0);
    if (g != 0 && (d = dldBase(*(unsigned int **)(GetScriptClass(g) + 0x48))) != 0)
        *(float *)(w + 0x18) = *(float *)(d + 4);
    *(int *)(w + 0x2C) = 0;
    ((Vec4 *)(w + 0x30))->q = ((Vec4 *)*(int *)(l + 0x134))->q;
    ((Vec4 *)(w + 0x40))->q = YUnitVector.q;
    isysJumpSubThread(func_000B4A80, w);
}
