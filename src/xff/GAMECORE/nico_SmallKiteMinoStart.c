typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } __attribute__((aligned(16))) V;

extern char rootPtn[];
extern char gcGlobalVar[];
extern int ControlMode_KITE_DEFAULT;
extern int ControlMode_KITE_TAKEOFF;
extern int ControlMode_KITE_FLY;
extern int ControlMode_KITE_SURFING;
extern int ControlMode_KITE_LANDING;
extern int ControlMode_MINOTOUR_KITE_SURFING;
extern int ControlMode_MINOTOUR_KITE_FLY;
extern V ZUnitVector;
extern V ZeroVector;
extern V IdentityQuaternion;
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
        *(int *)(w + 0x25C) = 2;
        *(int *)(w + 0x260) = 2;
        *(int *)(w + 0x264) = 2;
    } else if (id == 0x10) {
        *(int *)(w + 0x25C) = 3;
        *(int *)(w + 0x258) = 3;
        *(int *)(w + 0x260) = 3;
        *(int *)(w + 0x264) = 3;
    } else {
        *(int *)(w + 0x25C) = 2;
        *(int *)(w + 0x258) = 2;
        *(int *)(w + 0x260) = 2;
        *(int *)(w + 0x264) = 2;
    }
    *(volatile int *)(w + 0x26C) = 10;
    *(volatile float *)(w + 0x270) = 10.0f;
    *(volatile float *)(w + 0x2D8) = 1.0f;
    *(char * volatile *)(w + 0x220) = w + 0x40;
    *(volatile int *)(w + 0x2DC) = 0;
    *(volatile int *)(w + 0x2E0) = 0;
    *(volatile int *)(w + 0x2C0) = 0;
    *(volatile int *)(w + 0x310) = 0;
    *(volatile int *)(w + 0x314) = 0;
    *(volatile int *)(w + 0x318) = 0;
    *(volatile int *)(w + 0x31C) = 0;
    *(volatile float *)(w + 0x2C4) = 1.0f;
    *(volatile float *)(w + 0x2C8) = 1.0f;
    *(volatile float *)(w + 0x2CC) = 1.0f;
    *(volatile float *)(w + 0x2D0) = 1.0f;
    *(volatile float *)(w + 0x2D4) = 1.0f;
    *(volatile int *)(w + 0x280) = 0;
    *(volatile int *)(w + 0x284) = 0;
    *(volatile int *)(w + 0x288) = 0;
    *(volatile int *)(w + 0x28C) = 0;
    *(volatile int *)(w + 0x290) = 0;
    *(volatile int *)(w + 0x274) = 0;
    *(volatile int *)(w + 0x278) = 0;
    *(volatile int *)(w + 0x27C) = 0;
    *(volatile int *)(w + 0x320) = 0;
    ((V *)(w + 0x230))->q = ZUnitVector.q;
    ((V *)(w + 0x300))->q = ZeroVector.q;
    ((V *)(w + 0x2F0))->q = ZeroVector.q;
    *(volatile float *)(w + 0x2F8) = *(float *)(*(char **)(w + 0x34) + 0xC);
    ((V *)(w + 0x2A0))->q = IdentityQuaternion.q;
    isysJumpSubThread(func_000AC1C0, w);
}
