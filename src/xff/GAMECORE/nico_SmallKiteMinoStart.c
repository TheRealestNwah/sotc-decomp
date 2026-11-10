#ifdef NONMATCHING
/* 68 diffs, 1 word long (161 vs 160). Draft from the asm; sibling of the nico_SmallKite*Start functions (partition 0x383, work 0x350, no path work). Waits for the first player object, inits the animal work with id 0, maps the control mode (kite default / takeoff / fly / surfing / landing / minotaur variants) to an animal state 0xD..0x11, writes the state table at +0x250..+0x264 (fly -> 2s, surfing -> 3s, otherwise 2s), then the constant block and vector copies (ZUnitVector, ZeroVector x2, IdentityQuaternion) and jumps to func_000AC1C0. Remaining differences are store scheduling only: the Original keeps source order for the 0x2C4..0x2D4 float stores and the vector copies, ours interleaves them with the 0x26C/0x270 setup, and the fly/else store order in the state table differs. Permuter (12 workers, 15 min): score 2020 -> 1080, but its best version has more differing words (76) than this draft. */
typedef int s128 __attribute__((mode(TI)));

extern char rootPtn[];
extern char gcGlobalVar[];
extern int ControlMode_KITE_DEFAULT;
extern int ControlMode_KITE_TAKEOFF;
extern int ControlMode_KITE_FLY;
extern int ControlMode_KITE_SURFING;
extern int ControlMode_KITE_LANDING;
extern int ControlMode_MINOTOUR_KITE_SURFING;
extern int ControlMode_MINOTOUR_KITE_FLY;
extern s128 ZUnitVector;
extern s128 ZeroVector;
extern s128 IdentityQuaternion;
extern void *isysGetThisSubThread(void);
extern int iosCreatePartition(void *, int);
extern char *GetScriptCharacterClass(void *);
extern char *GetCharacterClass(void *);
extern void CharaCtrlResetCtrlStatus(void *);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern char *_SCRMallocAlign(int, int, int);
extern void isysJumpSubThread(void (*)(void), void *);
extern char *GetScriptClass(void *);
extern char *getEditWorkInitData(int);
extern void *SCRGetFirstObj(void *);
extern void scrRun(void);
extern void AI_InitAnimalWork(void *, int);
extern void func_000AC1C0(void);

void nico_SmallKiteMinoStart(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, 0x383);
    char *c;
    char *w;
    int mode;
    int id;

    *(int *)(GetScriptCharacterClass(th) + 0x11FC) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScriptCharacterClass(th);
    w = _SCRMallocAlign(part, 0x350, 0x10);
    *(char **)(c + 0x1200) = w;
    *(char **)(w + 0x34) = getEditWorkInitData(*(int *)(GetScriptClass(th) + 0x40));
    CharaCtrlResetCtrlStatus(th);
    while ((*(void **)(w + 0x20) = SCRGetFirstObj(gcGlobalVar + 0x2B0)) == 0)
        scrRun();
    AI_InitAnimalWork(w, 0);
    mode = *(int *)(GetCharacterClass(isysGetThisSubThread()) + 0x750);
    if (mode == ControlMode_KITE_DEFAULT)
        id = 0xD;
    else if (mode == ControlMode_KITE_TAKEOFF)
        id = 0xE;
    else if (mode == ControlMode_KITE_FLY)
        id = 0xF;
    else if (mode == ControlMode_KITE_SURFING)
        id = 0x10;
    else if (mode == ControlMode_KITE_LANDING)
        id = 0x11;
    else if (mode == ControlMode_MINOTOUR_KITE_SURFING)
        id = 0x10;
    else
        id = mode == ControlMode_MINOTOUR_KITE_FLY ? 0xF : 0xD;
    *(int *)(w + 0x250) = id;
    *(int *)(w + 0x258) = 2;
    if (id == 0xF) {
        *(int *)(w + 0x264) = 2;
        *(int *)(w + 0x25C) = 2;
    } else if (id == 0x10) {
        *(int *)(w + 0x264) = 3;
        *(int *)(w + 0x25C) = 3;
        *(int *)(w + 0x258) = 3;
        *(int *)(w + 0x260) = 3;
        goto done;
    } else {
        *(int *)(w + 0x264) = 2;
        *(int *)(w + 0x25C) = 2;
        *(int *)(w + 0x258) = 2;
    }
    *(int *)(w + 0x260) = 2;
done:
    *(int *)(w + 0x26C) = 10;
    *(float *)(w + 0x270) = 10.0f;
    *(float *)(w + 0x2D8) = 1.0f;
    *(char **)(w + 0x220) = w + 0x40;
    *(int *)(w + 0x2DC) = 0;
    *(int *)(w + 0x2E0) = 0;
    *(int *)(w + 0x2C0) = 0;
    *(int *)(w + 0x310) = 0;
    *(int *)(w + 0x314) = 0;
    *(int *)(w + 0x318) = 0;
    *(int *)(w + 0x31C) = 0;
    *(float *)(w + 0x2C4) = 1.0f;
    *(float *)(w + 0x2C8) = 1.0f;
    *(float *)(w + 0x2CC) = 1.0f;
    *(float *)(w + 0x2D0) = 1.0f;
    *(float *)(w + 0x2D4) = 1.0f;
    *(int *)(w + 0x280) = 0;
    *(int *)(w + 0x284) = 0;
    *(int *)(w + 0x288) = 0;
    *(int *)(w + 0x28C) = 0;
    *(int *)(w + 0x290) = 0;
    *(int *)(w + 0x274) = 0;
    *(int *)(w + 0x278) = 0;
    *(int *)(w + 0x27C) = 0;
    *(int *)(w + 0x320) = 0;
    *(s128 *)(w + 0x230) = ZUnitVector;
    *(s128 *)(w + 0x300) = ZeroVector;
    *(s128 *)(w + 0x2F0) = ZeroVector;
    *(float *)(w + 0x2F8) = *(float *)(*(char **)(w + 0x34) + 0xC);
    *(s128 *)(w + 0x2A0) = IdentityQuaternion;
    isysJumpSubThread(func_000AC1C0, w);
}
#endif
