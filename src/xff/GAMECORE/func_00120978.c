typedef struct Ptn Ptn;

typedef struct {
    int obj;
    int p0;
    char *p1;
    int p2;
    int f10;
    int p3;
    int bgm;
    int f1C;
    int p4;
    int p7;
    float fp;
    float f2C;
    int flag;
    unsigned int *p6;
    int p8;
    int f3C;
    int f40;
    int f44;
    int p9;
    int f4C;
    int f50;
    int sobj;
} DemoSlot;

extern int *DldSysUndefSymbol;
extern struct {
    int a;
    int b;
    int trig;
} padManagerData;
typedef struct {
    char pad0[0x178];
    float timer;
    char pad17C[4];
    float dt;
} GcGlobal;

extern GcGlobal gcGlobalVar;
extern Ptn rootPtn;
extern char RO_001816E0[];
extern void T_00120848(void *);
extern void func_00121390(void *);
extern void gameflowSetPauseEnable(int);
extern int bgmStandby(int, int, void (*)(void *), void *);
extern void bgmPlay(int, float);
extern void bgmStop(int, int, float);
extern void scrRun(void);
extern int gcCreateScriptObj(void (*)(void *), void *, Ptn *, int, int, int, char *);
extern void _gameFlagSet(int);
extern void _gameFlagCls(int);
extern void gameflowBossEyeCameraDisable(int);
extern void _SCRStartLWS(int, int, int, void *);
extern int execCondition(int, unsigned int *, unsigned int *);
extern void fadeOut(int, int, float);
extern void fadeIn(int, int, float);
extern int get_main_cameraman(void);
extern void compel_end_lws_movie_mode_game_camera(int);
extern void SCRDeleteAllActiveScriptAnimationObj(void);
extern float getDemoBarFade(void);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static inline void skipCheck(int skip, int *done)
{
    if (skip && (padManagerData.trig & 0x800)) {
        if (*done == 0)
            fadeOut(1, 0, 0.4f);
        *done = 1;
    }
}

static void func_00120978(DemoSlot *s)
{
    int skip = 0;
    int bgmFade = 0;
    float t;
    char *lws;

    s->f50 = 0;
    if (s == 0)
        return;
    if (s->p9 & 1)
        gameflowSetPauseEnable(0);
    if (s->p3 != 0) {
        {
            int m = s->p9 & 2;
            bgmFade = m == 0;
        }
        while ((s->bgm = bgmStandby(s->p3, 0, func_00121390, s)) == 0)
            scrRun();
        bgmPlay(s->bgm, 100.0f);
    } else {
        s->f1C = 1;
    }
    if (s->p8 != 0) {
        s->f3C = 0;
        s->f40 = 0;
        s->sobj = gcCreateScriptObj(T_00120848, s, &rootPtn, 0x1000, 0, 0xA, RO_001816E0);
        while (s->f3C == 0)
            scrRun();
    }
    if (s->p4 != 0)
        _gameFlagSet(s->p4);
    if (s->p7 != 0)
        _gameFlagCls(s->p7);
    lws = s->p1;
    if (lws != 0) {
        s->f4C = 1;
        gameflowBossEyeCameraDisable(1);
        scrRun();
        _SCRStartLWS(*(int *)(lws + 8), -1, s->p2, s->p2 == 5 ? 0 : &s->f10);
        if (!(s->p9 & 1))
            skip = 1;
    } else {
        bgmFade = 0;
        s->f10 = 1;
        skip = 0;
    }
    if (dldResolve(s->p6) != 0) {
        while (execCondition(s->p0, s->p6, s->p6) != 0 && s->f10 == 0 && s->f50 == 0) {
            s->f2C += gcGlobalVar.dt;
            scrRun();
            skipCheck(skip, &s->f50);
        }
    } else {
        while (s->f10 == 0 && s->f50 == 0) {
            s->f2C += gcGlobalVar.dt;
            scrRun();
            skipCheck(skip, &s->f50);
        }
    }
    while (s->f2C < s->fp && s->f50 == 0) {
        s->f2C += gcGlobalVar.dt;
        scrRun();
        skipCheck(skip, &s->f50);
    }
    if (s->p8 != 0 && s->f50 == 0) {
        while (s->f40 == 0) {
            scrRun();
            skipCheck(skip, &s->f50);
        }
    }
    if (s->f10 == 0 && s->p1 != 0) {
        _SCRStartLWS(*(int *)(s->p1 + 8), -1, 1, 0);
        s->f10 = 1;
    }
    if (s->f50 != 0) {
        compel_end_lws_movie_mode_game_camera(get_main_cameraman());
        SCRDeleteAllActiveScriptAnimationObj();
        scrRun();
        if (s->bgm != 0 && (s->p8 != 0 || bgmFade)) {
            bgmStop(s->bgm, 0, 5.0f);
            s->bgm = 0;
            s->f1C = 1;
        }
        t = gcGlobalVar.timer;
        while (gcGlobalVar.timer - t < 0.2f)
            scrRun();
        fadeIn(0, 0, 1.0f);
    }
    if (s->f4C != 0) {
        s->f4C = 0;
        gameflowBossEyeCameraDisable(0);
    }
    if (s->p9 & 1) {
        s->p9 &= ~1;
        gameflowSetPauseEnable(1);
    }
    if (s->f1C == 0 && bgmFade) {
        while (getDemoBarFade() == 0.0f)
            scrRun();
        if (s->f1C != 0) {
            bgmStop(s->bgm, 0, 1.0f);
            s->f1C = 1;
        }
    }
    if (s->flag != 0)
        _gameFlagCls(s->flag);
    while (s->f1C == 0)
        scrRun();
}
