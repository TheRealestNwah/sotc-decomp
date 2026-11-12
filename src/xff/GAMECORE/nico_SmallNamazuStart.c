typedef int s128 __attribute__((mode(TI)));

extern char rootPtn[], gcGlobalVar[], ZeroVector[], XUnitVector[], IdentityQuaternion[];
extern char SH_SmallAnimalTypeDEFAULT[];
extern int ControlMode_NAMAZU_DEFAULT, ControlMode_NAMAZU_MOVE, ControlMode_NAMAZU_TURN, ControlMode_NAMAZU_DEATH;
extern float RO_001801CC;
extern int isysGetThisSubThread(void);
extern int iosCreatePartition(void *, int);
extern char *GetScriptCharacterClass(int);
extern char *GetCharacterClass(int);
extern char *GetScriptClass(int);
extern char *GetLayoutClass(int);
extern char *getSObjNode(int);
extern void CharaCtrlResetCtrlStatus(int);
extern void CharaCtrlResetAllScriptCtrlStatus(int);
extern char *_SCRMallocAlign(char *, int, int);
extern char *getEditWorkInitData(int);
extern void scrRun(void);
extern char *SCRGetFirstObj(void *);
extern void AI_InitAnimalWork(char *, int);
extern void AI_InitAnimalOptimize(char *);
extern void GAMEUTIL_get_object_scale(char *, int);
extern void isysJumpSubThread(void (*)(void), int);
extern void func_000BB520(void);
extern void *DldSysUndefSymbol;

static inline char *dldData(unsigned int *reference)
{
    unsigned int offset = *reference & 0x3FFFF;
    char *module = offset ? *(char **)((char *)reference - offset) : 0;
    if (module == 0 || module == DldSysUndefSymbol)
        return 0;
    return *(char **)(module + 0x10);
}

#ifdef NONMATCHING /* 228 diffs, 241 vs 246 words: field-init store order and dld-resolve branch forms; some sequences (0x178 selection, control-mode movn) differ */
void nico_SmallNamazuStart(void)
{
    int thr = isysGetThisSubThread();
    char *s2, *s1, *o, *lay, *node, *tbl, *v;
    int mode, c, st;
    float sc;

    iosCreatePartition(rootPtn, 0x343);
    s2 = GetScriptCharacterClass(thr);
    *(char **)(GetScriptCharacterClass(thr) + 0x11FC) = s2;
    CharaCtrlResetCtrlStatus(thr);
    CharaCtrlResetAllScriptCtrlStatus(thr);
    s1 = GetScriptCharacterClass(thr);
    o = _SCRMallocAlign(s2, 0x310, 0x10);
    *(char **)(s1 + 0x1200) = o;
    *(char **)(o + 0x64) = getEditWorkInitData(*(int *)(GetScriptClass(thr) + 0x40));
    CharaCtrlResetCtrlStatus(thr);
    while ((*(char **)(o + 0x40) = SCRGetFirstObj(gcGlobalVar + 0x2B0)) == 0)
        scrRun();
    AI_InitAnimalWork(o, 3);
    AI_InitAnimalOptimize(o + 0x14);
    *(int *)(o + 0x158) = 0;
    *(int *)(o + 0x16C) = 0x1A;
    *(int *)(o + 0x178) = 0x1A;
    *(int *)(o + 0x174) = 0x10;
    *(int *)(o + 0x15C) = 1;
    *(int *)(o + 0x160) = 1;
    *(int *)(o + 0x164) = 1;
    *(int *)(o + 0x170) = 0x10;
    *(s128 *)(o + 0x210) = *(s128 *)ZeroVector;
    *(int *)(o + 0x234) = 0;
    *(int *)(o + 0x238) = 0;
    *(int *)(o + 0x23C) = 0;
    *(int *)(o + 0x184) = 0;
    *(float *)(o + 0x24C) = RO_001801CC;
    *(float *)(o + 0x264) = 1.0f;
    *(float *)(o + 0x260) = 1.0f;
    *(float *)(o + 0x180) = *(float *)(*(char **)(o + 0x64) + 0xB0);
    *(int *)(o + 0x304) = 1;
    *(int *)(o + 0x188) = 0;
    *(int *)(o + 0x18C) = 0;
    *(int *)(o + 0x190) = 0;
    *(int *)(o + 0x194) = 0;
    *(int *)(o + 0x198) = 0;
    *(int *)(o + 0x19C) = 0;
    *(int *)(o + 0x240) = 0;
    *(int *)(o + 0x2F4) = 0;
    *(int *)(o + 0x2A0) = 0;
    *(s128 *)(o + 0x130) = *(s128 *)XUnitVector;
    *(s128 *)(o + 0x1E0) = *(s128 *)ZeroVector;
    *(s128 *)(o + 0x200) = *(s128 *)ZeroVector;
    *(float *)(o + 0x1A4) = *(float *)(*(char **)(GetCharacterClass(isysGetThisSubThread()) + 0x1140) + 0x88);
    *(s128 *)(o + 0x290) = *(s128 *)IdentityQuaternion;
    *(s128 *)(o + 0x280) = *(s128 *)IdentityQuaternion;
    *(int *)(o + 0x26C) = 0;
    *(s128 *)(o + 0x270) = *(s128 *)XUnitVector;
    thr = isysGetThisSubThread();
    mode = *(int *)(GetCharacterClass(isysGetThisSubThread()) + 0x750);
    if (mode == ControlMode_NAMAZU_DEFAULT)
        c = 0x21;
    else if (mode == ControlMode_NAMAZU_MOVE)
        c = 0x22;
    else if (mode == ControlMode_NAMAZU_TURN)
        c = 0x23;
    else
        c = (mode == ControlMode_NAMAZU_DEATH) ? 0x21 : 0x25;
    *(int *)(o + 0x150) = c;
    *(int *)(o + 0x178) = (c == 0x22) ? 0x1A : 0x1B;
    *(int *)(o + 0x17C) = 0x19;
    GAMEUTIL_get_object_scale(o + 0x50, thr);
    sc = (*(float *)(o + 0x50) + *(float *)(o + 0x54) + *(float *)(o + 0x58)) / 3.0f;
    *(float *)(o + 0x60) = sc;
    *(char *)(GetCharacterClass(thr) + 0xA25) = 1;
    thr = isysGetThisSubThread();
    node = getSObjNode(thr);
    lay = GetLayoutClass(thr);
    if (node) {
        tbl = *(char **)(SH_SmallAnimalTypeDEFAULT + 0x10);
        if (tbl)
            *(int *)(o + 0x304) = *(int *)(tbl + *(short *)(node + 0x34) * 0x34 + 0x2C);
        *(int *)(o + 4) = *(short *)(node + 0x50);
        *(int *)(o + 8) = *(short *)(node + 0x52);
        *(s128 *)(o + 0x20) = *(s128 *)(node + 0x20);
        *(float *)(o + 0x30) = *(float *)(node + 0x30);
        *(float *)(o + 0x34) = *(float *)(node + 0x40);
    } else {
        *(int *)(o + 8) = 0;
        *(int *)(o + 4) = -1;
        *(s128 *)(o + 0x20) = **(s128 **)(lay + 0x134);
        *(float *)(o + 0x30) = 10.0f;
        *(float *)(o + 0x34) = 3.0f;
    }
    v = dldData(*(unsigned int **)(GetScriptClass(isysGetThisSubThread()) + 0x48));
    if (v)
        *(float *)(o + 0x18) = *(float *)(v + 4);
    isysJumpSubThread(func_000BB520, 0);
}
#endif
