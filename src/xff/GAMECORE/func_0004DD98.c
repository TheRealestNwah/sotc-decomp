extern void *ScriptAnimationObjDef_FILM_BURN_TEST;
extern char ZeroPoint[];
extern char IdentityQuaternion[];
extern int FsEffect_FILM_BURN;
extern int SeList_film_burn;
extern struct { char pad[0x170]; float speed; } gcGlobalVar;
extern char RO_0017D2F0[];

extern void *_SCRSetupLWSIgnorePause(void *, int, void *, void *, void *);
extern void _SCRStartLWSIgnorePause(void *, int, int, int);
extern char *texSearchMopByName(char *);
extern void texClutReset(char *);
extern void PauseGame(int);
extern void ReleaseGame(int);
extern void sePlaySystemSound(int);
extern void fsEffectSetParam(int);
extern int texClutScrollOne(char *, char *, char *, char *, int, int);
extern void fadeOut(int, float, int);
extern void fadeIn(float, int, int);
extern int fadeCheck(void);
extern void scrRun(void);
extern void scrRunM(int);

static void func_0004DD98(void *arg)
{
    void *obj = _SCRSetupLWSIgnorePause(ScriptAnimationObjDef_FILM_BURN_TEST, 0, ZeroPoint, IdentityQuaternion, arg);
    float t = 0.0f;
    char *mop = texSearchMopByName(RO_0017D2F0);
    char *tex = *(char **)(mop + 0x20);
    char *clut = *(char **)(tex + 0xC);
    char *p = tex + 0x20;

    *(int *)(p + 0x44) = 0xFF;
    *(int *)(p + 0x48) = 1;
    *(int *)(p + 0x50) = 1;
    *(int *)(p + 0x40) = 0;
    *(short *)(clut + 8) = 0;
    *(short *)(clut + 0xA) = 0;
    texClutReset(mop);
    PauseGame(1);
    sePlaySystemSound(SeList_film_burn);
    _SCRStartLWSIgnorePause(obj, -1, 3, 0);
    while (1) {
        float a, b;
        fsEffectSetParam(FsEffect_FILM_BURN);
        a = (int)(t * 30.0f);
        *(int *)(p + 0x4C) = 0x10;
        t += gcGlobalVar.speed;
        b = (int)(t * 30.0f);
        if (texClutScrollOne(mop, tex, p, clut, (int)(b - a), 1)) {
            *(int *)(p + 0x4C) = 0;
            fadeOut(0, 1.0f, 0);
            break;
        }
        *(int *)(p + 0x4C) = 0;
        scrRun();
    }
    while (fadeCheck()) {
        fsEffectSetParam(FsEffect_FILM_BURN);
        scrRun();
    }
    scrRunM(0x5A);
    fadeIn(0.39999998f, 1, 0);
    ReleaseGame(1);
}
