#include "common.h"
#include "gamecore/scr_demo_manager.h"

typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

extern char gcGlobalVar[];
extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int, int, int, void *, int);
static inline void vecScale(void *out, void *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         : : "r"(v), "r"(s), "r"(out) : "memory");
}
static inline void vecAdd(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nlqc2 vf6, 0x0(%1)\nvadd.xyz vf5, vf5, vf6\nsqc2 vf5, 0x0(%2)\n"
                         : : "r"(a), "r"(b), "r"(out) : "memory");
}
static inline void vecSub(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nlqc2 vf6, 0x0(%1)\nvsub.xyz vf5, vf5, vf6\nsqc2 vf5, 0x0(%2)\n"
                         : : "r"(a), "r"(b), "r"(out) : "memory");
}
extern unsigned long *GetCollisionDBAttributeAdr(void *surface);
extern int *DldSysUndefSymbol;
extern void (*D_0017B8B0)(int);
extern int D_0017B8B4;
extern struct {
    int a;
    int b;
    int trig;
} padManagerData;
extern char *getSCRDataCtrlWork(void);
extern void gameflowSetPauseEnable(int);
extern void CharaCtrlSetScriptCtrlStatus(int, int);
extern int get_main_cameraman(void);
extern int is_playing_lws_movie_now_game_camera(int);
extern void scrRun(void);
extern void scrRunM(int);
extern void PauseGame(int);
extern void ReleaseGame(int);
extern void bgmPlayerDemoEndTypeAllClose(void);
extern void fadeOut(int, int, float);
extern void fadeIn(int, int, float);
extern void compel_end_lws_movie_mode_game_camera(int);
extern void SCRDeleteAllActiveScriptAnimationObj(void);
static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}
typedef struct {
    int obj;
    char pad04[0x34];
    int p8;
    int loaded;
    int f40;
    int f44;
    char pad48[8];
    int f50;
    int done;
} DemoSlot;
extern char SH_StageDataDEFAULT[];
extern int sheetMgrLoadSegmentIndex(char *, int, int *);
extern void sheetMgrUnloadSegmentIndex(char *, int, int);
extern void *isysGetThisSubThread(void);
extern void *DisplayCaptionTableBlock(char *, void *, int, int *);
extern void isysRequestDeleteObj(void *);
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
} DemoSlot_func_00120978;
typedef struct {
    char pad0[0x178];
    float timer;
    char pad17C[4];
    float dt;
} GcGlobal;
extern Ptn rootPtn;
extern char RO_001816E0[];
extern int bgmStandby(int, int, void (*)(void *), void *);
extern void bgmPlay(int, float);
extern void bgmStop(int, int, float);
extern int gcCreateScriptObj(void (*)(void *), void *, Ptn *, int, int, int, char *);
extern void _gameFlagSet(int);
extern void _gameFlagCls(int);
extern void gameflowBossEyeCameraDisable(int);
extern void _SCRStartLWS(int, int, int, void *);
extern int execCondition(int, unsigned int *, unsigned int *);
extern float getDemoBarFade(void);
static inline void skipCheck(int skip, int *done)
{
    if (skip && (padManagerData.trig & 0x800)) {
        if (*done == 0)
            fadeOut(1, 0, 0.4f);
        *done = 1;
    }
}
extern char RO_001816C8[];
extern void *_gcCreateChildScriptObj(void *, void *, void *, int, int, int, char *, void *);
extern int D_0017B8B8;
typedef struct { int on; char pad[0x14]; int id; int closed; char pad2[0x38]; } EvBgm;
extern EvBgm B_001A5A78[];
typedef struct {
    int obj;
    int p0;
    int p1;
    int p2;
    int f10;
    int p3;
    int bgm;
    int f1C;
    int p4;
    int p7;
    float fp;
    int f2C;
    int flag;
    int p6;
    int p8;
    char pad3C[8];
    int f44;
    int p9;
    int f4C;
    int f50;
    int done;
} DemoSlot_createScrEventDemoManager;
extern char RO_001816F8[];
extern void *getNowExecEventScriptObj(void);
extern void isysSetObjImmediateDeleteFunc(int, void (*)(int));
static inline DemoSlot_createScrEventDemoManager *getSlot(int p0, int p1, int p2, int p3, int p4, int flag, int p6, int p7, float fp, int p8, int p9)
{
    DemoSlot_createScrEventDemoManager *p;
    DemoSlot_createScrEventDemoManager *q;
    int i;

    for (i = 0, p = ((DemoSlot_createScrEventDemoManager *)&B_001A5A78); i < 2; i++, p++) {
        if (p->obj == 0)
            continue;
        if (p1 != 0) {
            if (p->p1 == p1)
                return 0;
        } else if (p3 != 0) {
            if (p->p3 == p3)
                return 0;
        } else if (p8 != 0) {
            if (p->p8 != 0)
                return 0;
        }
    }
    for (i = 0; i < 2; i++) {
        q = &((DemoSlot_createScrEventDemoManager *)&B_001A5A78)[i];
        if (q->obj == 0 && q->done == 0) {
            q->p0 = p0;
            q->p1 = p1;
            q->p2 = p2;
            q->p3 = p3;
            q->p4 = p4;
            q->fp = fp;
            q->p6 = p6;
            q->p7 = p7;
            q->p8 = p8;
            q->p9 = p9;
            q->f10 = 0;
            q->bgm = 0;
            q->f1C = 0;
            q->f2C = 0;
            q->flag = flag;
            q->f44 = 0;
            q->done = 0;
            q->f4C = 0;
            if (flag)
                _gameFlagSet(flag);
            return q;
        }
    }
    return 0;
}
extern void *memset(void *, int, unsigned int);
typedef struct {
    int obj;
    char pad4[0x14];
    int bgm;
    char pad1C[0x14];
    int flag;
    char pad34[0x10];
    int done;
    int attr;
    int eyeCamera;
    char pad50[8];
} DemoSlot_func_001212C8;
extern int flushScriptObjImmediate();
typedef struct {
    char pad0[0x18];
    int bgm;
    int stopped;
} BgmWork;

static int func_001205B0(void *surface);
static void func_001212C8(int obj);
static void func_00121390(int a0, int a1, int a2, int a3, BgmWork *work);

int SCRConditionAtkChackThreeRaySector(void *obj, float a, float b, float c)
{
    struct { Vec4 v10; char buf[0x50]; Vec4 v70; Vec4 v80; Vec4 v90; Vec4 vA0; Vec4 vB0; } L;
    int i;
    float fa;
    float fb;
    char *cc;

    if (c <= 0.0f)
        c = 0.1f;
    fa = a * c;
    fb = b * c;
    *(s128 *)&L.v70 = **(s128 **)(GetLayoutClass(obj) + 0x134);
    *(s128 *)&L.v10 = *(s128 *)(GetCharacterClass(obj) + 0x470);
    cc = GetCharacterClass(obj) + 0x470;
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubx.z vf6, vf0, vf5x\n"
                         "vsuby.z vf6, vf6, vf5y\n"
                         "vaddw.y vf6, vf7, vf7w\n"
                         "vsuby.x vf6, vf8, vf8y\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.z vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(&L.v80), "r"(cc) : "memory");
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubz.x vf6, vf7, vf7z\n"
                         "vaddx.y vf6, vf0, vf6x\n"
                         "vsuby.x vf6, vf0, vf5y\n"
                         "vsubz.x vf6, vf6, vf5z\n"
                         "vaddw.z vf6, vf8, vf8w\n"
                         "vsub.w vf6, vf6, vf6\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.x vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(&L.vB0), "r"(&L.v10) : "memory");
    for (i = 0; i < 3; i++) {
        if (i == 0) {
            vecScale(&L.vA0, &L.v80, fa);
            vecAdd(&L.v90, &L.v70, &L.vA0);
        } else if (i == 1) {
            vecScale(&L.vA0, &L.vB0, fb);
            vecAdd(&L.v90, &L.v70, &L.vA0);
            vecScale(&L.vA0, &L.v80, fa);
            vecAdd(&L.v90, &L.v90, &L.vA0);
        } else if (i == 2) {
            vecScale(&L.vA0, &L.vB0, fb);
            vecSub(&L.v90, &L.v70, &L.vA0);
            vecScale(&L.vA0, &L.v80, fa);
            vecAdd(&L.v90, &L.v90, &L.vA0);
        }
        if (ClipCollisionDirectCallBack(L.buf, &L.v70, &L.v90, gcGlobalVar + 0x238, 0, 0, 0, func_001205B0, 0) != 0)
            return 0;
    }
    return 1;
}

int SCRConditionAtkChackThreeRayParallel(void *obj, float a, float b, float c)
{
    struct { Vec4 v10; char buf[0x50]; Vec4 v70; Vec4 v80; Vec4 v90; Vec4 vA0; Vec4 vB0; Vec4 vC0; Vec4 vD0; Vec4 vE0; } L;
    int i;
    float fa;
    float fb;
    char *cc;
    Vec4 *pa;
    register s128 *pd __asm__("$19");

    if (c <= 0.0f)
        c = 0.1f;
    fa = a * c;
    fb = b * c;
    *(s128 *)&L.v70 = **(s128 **)(GetLayoutClass(obj) + 0x134);
    *(s128 *)&L.v10 = *(s128 *)(GetCharacterClass(obj) + 0x470);
    cc = GetCharacterClass(obj) + 0x470;
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubx.z vf6, vf0, vf5x\n"
                         "vsuby.z vf6, vf6, vf5y\n"
                         "vaddw.y vf6, vf7, vf7w\n"
                         "vsuby.x vf6, vf8, vf8y\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.z vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(&L.v80), "r"(cc) : "memory");
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubz.x vf6, vf7, vf7z\n"
                         "vaddx.y vf6, vf0, vf6x\n"
                         "vsuby.x vf6, vf0, vf5y\n"
                         "vsubz.x vf6, vf6, vf5z\n"
                         "vaddw.z vf6, vf8, vf8w\n"
                         "vsub.w vf6, vf6, vf6\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.x vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(&L.vC0), "r"(&L.v10) : "memory");
    vecScale(&L.vE0, &L.vC0, fb);
    *(s128 *)&L.v90 = *(s128 *)&L.v70;
    pd = (s128 *)&L.vD0;
    for (i = 0; i < 3; i++) {
        if (i == 1) {
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nlqc2 vf6, 0x0(%1)\nvadd.xyz vf5, vf5, vf6\nsqc2 vf5, 0x0(%2)\n"
                                 : : "r"(&L.v70), "r"(&L.vE0), "r"(pd) : "memory");
            *(s128 *)&L.v90 = *(s128 *)&L.vD0;
        }
        if (i == 2) {
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nlqc2 vf6, 0x0(%1)\nvsub.xyz vf5, vf5, vf6\nsqc2 vf5, 0x0(%2)\n"
                                 : : "r"(&L.v70), "r"(&L.vE0), "r"(pd) : "memory");
            *(s128 *)&L.v90 = *(s128 *)&L.vD0;
        }
        vecScale(&L.vB0, &L.v80, fa);
        pa = &L.vA0;
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nlqc2 vf6, 0x0(%1)\nvadd.xyz vf5, vf5, vf6\nsqc2 vf5, 0x0(%2)\n"
                             : : "r"(&L.v90), "r"(&L.vB0), "r"(&L.vA0) : "memory");
        if (ClipCollisionDirectCallBack(L.buf, &L.v90, pa, gcGlobalVar + 0x238, 0, 0, 0, func_001205B0, 0) != 0)
            return 0;
    }
    return 1;
}

static int func_001205B0(void *surface)
{
    return (*GetCollisionDBAttributeAdr(surface) & 0xF80000000) == 0x600000000;
}

static void func_001205F0(int obj)
{
    unsigned int *h = *(unsigned int **)(getSCRDataCtrlWork() + 0x4168);
    char *e;
    int cam;

    gameflowSetPauseEnable(0);
    e = dldResolve(h);
    if (e != 0)
        CharaCtrlSetScriptCtrlStatus(obj, *(int *)(e + 4));
    while (is_playing_lws_movie_now_game_camera(get_main_cameraman()) == 0)
        scrRun();
    while (is_playing_lws_movie_now_game_camera(cam = get_main_cameraman()) != 0) {
        if (padManagerData.trig & 0x800) {
            PauseGame(1);
            bgmPlayerDemoEndTypeAllClose();
            if (D_0017B8B0 != 0) {
                D_0017B8B0(D_0017B8B4);
                D_0017B8B0 = 0;
            }
            fadeOut(1, 0, 0.4f);
            scrRunM(0x14);
            ReleaseGame(1);
            e = dldResolve(h + 1);
            if (e != 0) {
                CharaCtrlSetScriptCtrlStatus(obj, *(int *)(e + 4));
                scrRun();
            }
            compel_end_lws_movie_mode_game_camera(cam);
            SCRDeleteAllActiveScriptAnimationObj();
            fadeIn(0, 0, 1.0f);
            break;
        }
        scrRun();
    }
    if (D_0017B8B0 != 0) {
        D_0017B8B0(D_0017B8B4);
        D_0017B8B0 = 0;
    }
    gameflowSetPauseEnable(1);
}

static void T_00120848(DemoSlot *s)
{
    int st[2];
    char *sh = SH_StageDataDEFAULT;
    register char *e __asm__("$16");

    sheetMgrLoadSegmentIndex(sh, s->p8, &st[0]);
    while (!(st[0] == 0xDEAF || st[0] == 0xDEB0))
        scrRun();
    s->loaded = 1;
    e = *(char **)(sh + 0x10);
    e += s->p8 * 20;
    if (s->f44 == 0) {
        e = DisplayCaptionTableBlock(e + 4, isysGetThisSubThread(), 3, &st[1]);
        while (st[1] == 0 && s->f50 == 0)
            scrRun();
        if (st[1] == 0)
            isysRequestDeleteObj(e);
    }
    if (s->obj != 0)
        s->f40 = 1;
    sheetMgrUnloadSegmentIndex(sh, s->p8, 0);
    s->done = 0;
}

static void func_00120978(DemoSlot_func_00120978 *s)
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
            s->f2C += (*(GcGlobal *)&gcGlobalVar).dt;
            scrRun();
            skipCheck(skip, &s->f50);
        }
    } else {
        while (s->f10 == 0 && s->f50 == 0) {
            s->f2C += (*(GcGlobal *)&gcGlobalVar).dt;
            scrRun();
            skipCheck(skip, &s->f50);
        }
    }
    while (s->f2C < s->fp && s->f50 == 0) {
        s->f2C += (*(GcGlobal *)&gcGlobalVar).dt;
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
        t = (*(GcGlobal *)&gcGlobalVar).timer;
        while ((*(GcGlobal *)&gcGlobalVar).timer - t < 0.2f)
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

void *createScrDemoManager(void *parent)
{
    return _gcCreateChildScriptObj(func_001205F0, parent, ((char *)&rootPtn), 0x4000, 0, 4, RO_001816C8, parent);
}

void setScrDemoMangerFinishCallback(int arg0, int arg1)
{
    *(int *)&D_0017B8B0 = arg0;
    D_0017B8B4 = arg1;
}

void pauseEventDemoManger(int on)
{
    int *p = &D_0017B8B8;
    int v;

    if (on == 1)
        v = *p + 1;
    else
        v = *p - 1;
    *p = v;
}

void eventBgmAllClose(void)
{
    EvBgm *e = B_001A5A78;
    int i;
    for (i = 0; i < 2; i++, e++) {
        if (e->on != 0 && e->closed == 0) {
            bgmStop(e->id, 0, 5.0f);
            e->closed = 1;
        }
    }
}

void createScrEventDemoManager(int p0, int p1, int p2, int p3, int p4, int flag, int p6, int p7, float fp, int p8, int p9)
{
    DemoSlot_createScrEventDemoManager *slot;

    if (D_0017B8B8 > 0)
        return;
    slot = getSlot(p0, p1, p2, p3, p4, flag, p6, p7, fp, p8, p9);
    if (slot) {
        slot->obj = _gcCreateChildScriptObj(func_00120978, slot, &rootPtn, 0x4000, 0, 4,
                                            RO_001816F8, getNowExecEventScriptObj());
        isysSetObjImmediateDeleteFunc(slot->obj, func_001212C8);
    }
}

void scrDemoInit(void)
{
    memset(((char *)&B_001A5A78), 0, 0xB0);
}

static void func_001212C8(int obj)
{
    DemoSlot_func_001212C8 *slot = ((DemoSlot_func_001212C8 *)&B_001A5A78);
    int i;

    for (i = 0; i < 2; i++, slot++) {
        if (obj == slot->obj) {
            slot->done = 1;
            if (slot->eyeCamera)
                gameflowBossEyeCameraDisable(0);
            if (slot->attr & 1)
                gameflowSetPauseEnable(1);
            if (slot->flag)
                _gameFlagCls(slot->flag);
            if (slot->bgm)
                ((void (*)(int, int *, float))bgmStop)(slot->bgm, 0, 100.0f);
            slot->obj = 0;
            flushScriptObjImmediate(obj);
            return;
        }
    }
}

static void func_00121390(int a0, int a1, int a2, int a3, BgmWork *work)
{
    if (work->bgm != 0) {
        bgmStop(work->bgm, 0, 100.0f);
        work->stopped = 1;
        work->bgm = 0;
    }
}
