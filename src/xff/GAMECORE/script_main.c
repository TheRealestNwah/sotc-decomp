extern int ScriptSpriteMenuObjDef_SPRITE_BOOT_PROGRESSIVE_ALERT;
extern void _SCRStartSpriteMenuAnim(int, int, int, int, int, int);
typedef struct {
    char pad0[0x188];
    float clipDist;
    char pad18C[0x1AC - 0x18C];
    int busy;
} GcGlobal_func_00095428;
extern int B_0018B850[4];
extern void func_00095E70(void);
extern void func_00096010(void);
extern void func_00095DB0(void);
extern void func_00095F50(void);
extern void isysLetterObjDiscardLetterAll(void *);
extern void isysSleepSubThread(void);
extern void FlushRequestViewIntervalClip(void *);
extern int get_main_cameraman_camera_obj(void);
extern void ExecScriptLayoutObj(void *);
extern char *GetCharacterClass(void *);
extern void ExecCharaGeometryPostprocess(void *);
typedef struct {
    char pad0[0x178];
    float geomCtx;
    char pad17C[0x188 - 0x17C];
    float clipDist;
} GcGlobal;
typedef struct {
    char pad0[0x370];
    short state;
    char pad372[0x534 - 0x372];
    signed char active;
    char pad535[0xD90 - 0x535];
    unsigned char riding;
    char padD91[0x1070 - 0xD91];
    int f1070;
    char pad1074[0x1170 - 0x1074];
    int f1170;
} ScrCharClass;
typedef struct {
    char pad0[0x8];
    unsigned char type;
} ScrObj;
extern GcGlobal gcGlobalVar;
extern int B_0019B860[2];
extern char B_0018B860[0x10000];
extern void *isysGetThisSubThread(void);
extern float ViewIntervalClip(void *, void *, float);
extern char *GetLayoutClass(void *);
extern int StageManagerCheckAreaExist(int);
extern ScrObj *SCRGetGetGeometryPointerLegalParentObj(char *);
extern void ExecCharaGeometryPreprocess(void *, float, float, float);
#define SCR_STACK_ENTER2()                                                                          __asm__ __volatile__("lui $2, %%hi(B_0019B860)\n"                                                                   "nop\n"                                                                                        "addiu $2, $2, %%lo(B_0019B860)\n"                                                             "nop\n"                                                                                        "sw $sp, 0($2)\n"                                                                              "la $3, B_0018B860\n"                                                                          "lui $2, %%hi(B_0019B860)\n"                                                                   "nop\n"                                                                                        "addiu $2, $2, %%lo(B_0019B860)\n"                                                             "nop\n"                                                                                        "move $sp, $2\n"                                                                               : : "r"(_scr_in) : "$2", "$5", "memory")
#define SCR_STACK_LEAVE2()                                                                          __asm__ __volatile__("lui $2, %%hi(B_0019B860)\n"                                                                   "nop\n"                                                                                        "addiu $2, $2, %%lo(B_0019B860)\n"                                                             "nop\n"                                                                                        "lw $sp, 0($2)\n"                                                                              : : "r"(*(volatile int *)B_0019B860) : "$2", "memory")
static inline int isOnRideParent(char *lay)
{
    ScrObj *obj;
    int t;

    if (lay == 0 || *(int *)(lay + 0x124) == 0 || (obj = SCRGetGetGeometryPointerLegalParentObj(lay + 0xC0)) == 0) {
        t = 0;
    } else {
        switch (obj->type) {
        case 9:
        case 0xD:
        case 0x16:
            t = 1;
            break;
        default:
            t = 0;
            break;
        }
    }
    return t;
}
typedef struct {
    char pad0[0x178];
    float geomCtx;
    char pad17C[0x188 - 0x17C];
    float clipDist;
    char pad18C[0x1AC - 0x18C];
    int busy;
    char pad1B0[0x370 - 0x1B0];
    char lws[0x10];
} GcGlobal_execObjectWithNonTaskSwitch;
extern void ExecCharaGeometry(void *, void *);
extern void ExecScriptLwsOrientClass(void *, void *, void *, float, float);
extern void iosJumpRecoverPoint(const char *, ...);
static inline void execLwsObj(ScrObj *obj)
{
    float clip;

    if ((*(GcGlobal_execObjectWithNonTaskSwitch *)&gcGlobalVar).busy) {
        FlushRequestViewIntervalClip(obj);
        ViewIntervalClip(obj, get_main_cameraman_camera_obj(), (*(GcGlobal_execObjectWithNonTaskSwitch *)&gcGlobalVar).clipDist);
    } else {
        clip = ViewIntervalClip(obj, get_main_cameraman_camera_obj(), (*(GcGlobal_execObjectWithNonTaskSwitch *)&gcGlobalVar).clipDist);
        ExecScriptLwsOrientClass(obj, get_main_cameraman_camera_obj(), (*(GcGlobal_execObjectWithNonTaskSwitch *)&gcGlobalVar).lws, clip, 1.0f / clip);
    }
    isysLetterObjDiscardLetterAll(obj);
}
typedef struct { char pad[0x1AC]; volatile int busy; } GVar;
extern void SetLayoutObjAccessSwitch(void *obj, int on);
extern void SetScriptAnimationObjAccessSwitch(void *obj, int on);
/* Called through an inline helper: the original makes a normal call here,
   not a tail call like the layout case. */
static inline void setScriptSwitch(unsigned char *obj, int on)
{
    SetScriptAnimationObjAccessSwitch(obj, on);
}
extern void *GetScriptCharacterClass(void *);
extern void func_00096168();
extern int D_0017AF54;
struct OrientationGlobalsView {
 char pad00[0x188];
  float interval;
 char pad18C[0x1E4];
 char context[0];
};
extern void func_000960C0();
typedef struct { char pad[0x178]; float f178; char pad2[0xC]; float f188; char pad3[0x1E4]; char geo[1]; } G;
static inline int isLegalParent(char *l)
{
    char *p;

    if (l != 0 && *(int *)(l + 0x124) != 0
        && (p = SCRGetGetGeometryPointerLegalParentObj(l + 0xC0)) != 0) {
        switch (*(unsigned char *)(p + 8)) {
        case 9:
        case 0xD:
        case 0x16:
            return 1;
        }
    }
    return 0;
}
extern char B_0019B868[];
extern int isysAddGroupWithLinkParam(void *, void *, int, int);
extern void isysInitGroup(void *);
extern char rootPtn[];
extern char RO_0017F8D8[];
extern void *gcCreateScriptObj(void *, int, void *, int, int, int, char *);
extern int *DldSysUndefSymbol;
extern int D_0017AF58;
extern int D_0017AF5C;
extern int D_0017AF60;
extern int D_0017AF64;
extern int D_0017AF68;
extern int D_0017AF6C;
extern char *gcGetStageData(int id);
extern void initlayout(int a0, void *a1, int a2, int a3, int t0, int t1);
/* Switches to the stage stack (B_0018B860, top saved in B_0019B860) around initlayout.
   The saved word is read into $a0 first; $3 is scratch the Original never declared.
   A bare block, not do/while(0): the loop form shifts every saved register. */
#define SCR_STACK_ENTER()                                                                          \
    {                                                                                              \
        register int top __asm__("$4") = *(volatile int *)B_0019B860;                              \
        __asm__ __volatile__("lui $2, %%hi(B_0019B860)\n"                                          \
                             "nop\n"                                                               \
                             "addiu $2, $2, %%lo(B_0019B860)\n"                                    \
                             "nop\n"                                                               \
                             "sw $sp, 0($2)\n"                                                     \
                             "la $3, B_0018B860\n"                                                 \
                             "lui $2, %%hi(B_0019B860)\n"                                          \
                             "nop\n"                                                               \
                             "addiu $2, $2, %%lo(B_0019B860)\n"                                    \
                             "nop\n"                                                               \
                             "move $sp, $2\n"                                                      \
                             :                                                                     \
                             : "r"(top)                                                            \
                             : "$2", "memory");                                                    \
    }
#define SCR_STACK_LEAVE()                                                                          \
    __asm__ __volatile__("lui $2, %%hi(B_0019B860)\n"                                              \
                         "nop\n"                                                                   \
                         "addiu $2, $2, %%lo(B_0019B860)\n"                                        \
                         "nop\n"                                                                   \
                         "lw $sp, 0($2)\n"                                                         \
                         :                                                                         \
                         : "r"(*(volatile int *)B_0019B860)                                        \
                         : "$2", "memory")
extern void func_00096610(void);
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);

static void func_000956B0(void);
static void func_000965E8(void);

void bootprogressivecheck(int a)
{
    _SCRStartSpriteMenuAnim(ScriptSpriteMenuObjDef_SPRITE_BOOT_PROGRESSIVE_ALERT, 0, 0, a, 0, 0);
}

static void func_00095428(unsigned char *obj)
{
    switch (obj[8]) {
    case 22:
        func_00095E70();
        isysLetterObjDiscardLetterAll(obj);
        isysSleepSubThread();
        while ((*(GcGlobal_func_00095428 *)&gcGlobalVar).busy) {
            FlushRequestViewIntervalClip(obj);
            ((void (*)(void *, int, float))ViewIntervalClip)(obj, get_main_cameraman_camera_obj(), (*(GcGlobal_func_00095428 *)&gcGlobalVar).clipDist);
            isysSleepSubThread();
        }
        break;
    case 6:
        isysLetterObjDiscardLetterAll(obj);
        isysSleepSubThread();
        return;
    case 29:
        isysLetterObjDiscardLetterAll(obj);
        isysSleepSubThread();
        func_00096010();
        while ((*(GcGlobal_func_00095428 *)&gcGlobalVar).busy) {
            isysLetterObjDiscardLetterAll(obj);
            isysSleepSubThread();
        }
        break;
    case 11:
        isysLetterObjDiscardLetterAll(obj);
        isysSleepSubThread();
        ExecScriptLayoutObj(obj);
        return;
    case 9:
        if (GetCharacterClass(obj)[0xCEC])
            func_00095DB0();
        ExecCharaGeometryPostprocess(obj);
        isysLetterObjDiscardLetterAll(obj);
        isysSleepSubThread();
        while ((*(GcGlobal_func_00095428 *)&gcGlobalVar).busy) {
            FlushRequestViewIntervalClip(obj);
            ((void (*)(void *, int, float))ViewIntervalClip)(obj, get_main_cameraman_camera_obj(), (*(GcGlobal_func_00095428 *)&gcGlobalVar).clipDist);
            isysSleepSubThread();
        }
        func_000956B0();
        return;
    case 13:
        func_00095F50();
        if (B_0018B850[0]) {
            for (;;) {
                isysLetterObjDiscardLetterAll(obj);
                isysSleepSubThread();
            }
        }
        isysLetterObjDiscardLetterAll(obj);
        isysSleepSubThread();
        while ((*(GcGlobal_func_00095428 *)&gcGlobalVar).busy) {
            isysLetterObjDiscardLetterAll(obj);
            isysSleepSubThread();
        }
        break;
    default:
        isysLetterObjDiscardLetterAll(obj);
        isysSleepSubThread();
        break;
    }
}

static void func_000956B0(void)
{
    void *thread;
    ScrCharClass *cc;
    float clip;

    {
        register int _scr_in asm("$4") = *(volatile int *)B_0019B860;
        SCR_STACK_ENTER2();
    }
    thread = isysGetThisSubThread();
    cc = GetCharacterClass(thread);
    clip = ViewIntervalClip(thread, get_main_cameraman_camera_obj(), gcGlobalVar.clipDist);
    if (cc->active != 0) {
        if (((ScrCharClass *)GetCharacterClass(thread))->f1170 == 0 || StageManagerCheckAreaExist(*(int *)(GetLayoutClass(thread) + 0x134)) != 0 ||
            cc->state == 4 || isOnRideParent(GetLayoutClass(thread)) || cc->riding == 1 || cc->f1070 == 1 || cc->state == 0xB) {
            ExecCharaGeometryPreprocess(thread, gcGlobalVar.geomCtx, clip, 1.0f / clip);
        }
    }
    SCR_STACK_LEAVE2();
}

void execObjectWithNonTaskSwitch(ScrObj *obj)
{
    ScrCharClass *cc;
    float clip;
    int ok;
    unsigned char t = obj->type;

    switch (t) {
    default:
        iosJumpRecoverPoint("scrsetup: execObjectWithNonTaskSwitch: \xa5\xb5\xa5\xdd\xa1\xbc\xa5\xc8\xa4\xb5\xa4\xec\xa4\xc6\xa4\xa4\xa4\xca\xa4\xa4\xa5\xaa\xa5\xd6\xa5\xb8\xa5\xa7\xa5\xaf\xa5\xc8:%s\xa4\xac\xa5\xc7\xa5\xd5\xa5\xa9\xa5\xeb\xa5\xc8" "AI\xbd\xe8\xcd\xfd\xa4\xcb\xa5\xa8\xa5\xf3\xa5\xc8\xa5\xea\xa4\xb5\xa4\xec\xa4\xc6\xa4\xa4\xa4\xde\xa4\xb9(\xbf\xf9)\n");
        return;
    case 9:
        if ((*(GcGlobal_execObjectWithNonTaskSwitch *)&gcGlobalVar).busy) {
            FlushRequestViewIntervalClip(obj);
            ViewIntervalClip(obj, get_main_cameraman_camera_obj(), (*(GcGlobal_execObjectWithNonTaskSwitch *)&gcGlobalVar).clipDist);
        } else {
            cc = (ScrCharClass *)GetCharacterClass(obj);
            clip = ViewIntervalClip(obj, get_main_cameraman_camera_obj(), (*(GcGlobal_execObjectWithNonTaskSwitch *)&gcGlobalVar).clipDist);
            ok = 0;
            if (cc->active != 0) {
                if (((ScrCharClass *)GetCharacterClass(obj))->f1170 == 0 || StageManagerCheckAreaExist(*(int *)(GetLayoutClass(obj) + 0x134)) != 0 ||
                    cc->state == 4 || isOnRideParent(GetLayoutClass(obj)) || cc->riding == 1 || cc->f1070 == 1 || cc->state == 0xB) {
                    ok = ((int (*)(void *, float, float, float))ExecCharaGeometryPreprocess)(obj, (*(GcGlobal_execObjectWithNonTaskSwitch *)&gcGlobalVar).geomCtx, clip, 1.0f / clip);
                }
            }
            if (ok) {
                char *c2 = (char *)GetCharacterClass(obj);
                ExecCharaGeometry(obj, (*(GcGlobal_execObjectWithNonTaskSwitch *)&gcGlobalVar).lws);
                c2[0x539] = StageManagerCheckAreaExist(*(int *)(GetLayoutClass(obj) + 0x134));
            }
            ExecCharaGeometryPostprocess(obj);
        }
        isysLetterObjDiscardLetterAll(obj);
        return;
    case 0x16:
        execLwsObj(obj);
        return;
    }
}

void scrRun(void)
{
    ((void (*)(void *thread))func_00095428)(isysGetThisSubThread());
}

void scrRunM(int n)
{
    void *t = isysGetThisSubThread();
    int i;
    for (i = 0; i < n; i++)
        ((void (*)(void *))func_00095428)(t);
}

void st_playObjAnim(void)
{
    void *t = isysGetThisSubThread();
    isysLetterObjDiscardLetterAll(t);
    isysSleepSubThread();
    while (((GVar *)((char *)&gcGlobalVar))->busy != 0) {
        isysLetterObjDiscardLetterAll(t);
        isysSleepSubThread();
    }
    for (;;)
        scrRun();
}

void SCRSetDispFlag(unsigned char *obj, int on)
{
    switch (obj[8]) {
    case 9:
    case 10:
    case 11:
        SetLayoutObjAccessSwitch(obj, on);
        break;
    case 13:
        setScriptSwitch(obj, on);
        break;
    /* Present in the original's case tree, with nothing to do. */
    case 14:
        break;
    }
}

void *GetSCRCharaAIWorkPtr(void *actor)
{
    void *script;

    script = GetScriptCharacterClass(actor);
    return *(void **)((char *)script + 0x1200);
}

int CheckSCRCharaAIWorkPtr(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (arg0 != 0) {
        var_v0 = (*(int *)((char *)(GetScriptCharacterClass((void *)arg0)) + 0x1200));
    }
    return var_v0;
}

void SCRSimpleExecCharaGeometry(int arg0)
{
    D_0017AF54 = arg0;
    func_00096168();
    D_0017AF54 = 0;
}

void scrInit(void)
{

}

void __execScrLwsOri(void *actor)
{
    float interval;

    interval = ViewIntervalClip(actor, get_main_cameraman_camera_obj(),
                                (*(struct OrientationGlobalsView *)&gcGlobalVar).interval);
    ExecScriptLwsOrientClass(actor, get_main_cameraman_camera_obj(),
                            (*(struct OrientationGlobalsView *)&gcGlobalVar).context, interval, 1.0f / interval);
}

void st_motionsyncanimation(void)
{
loop_1:
    func_000960C0();
    ((void (*)())isysSleepSubThread)();
    goto loop_1;
}

static void simpleExecCharaGeometry(int a0)
{
    int run = 0;
    char *c = ((char * (*)(int))GetCharacterClass)(a0);
    float clip = ((float (*)(int, int, float))ViewIntervalClip)(a0, get_main_cameraman_camera_obj(), (*(G *)&gcGlobalVar).f188);

    if (*(signed char *)(c + 0x534) != 0
        && (*(int *)(((char * (*)(int))GetCharacterClass)(a0) + 0x1170) == 0
            || StageManagerCheckAreaExist(*(int *)(((char * (*)(int))GetLayoutClass)(a0) + 0x134)) != 0
            || *(short *)(c + 0x370) == 4
            || isLegalParent(((char * (*)(int))GetLayoutClass)(a0))
            || *(unsigned char *)(c + 0xD90) == 1
            || *(int *)(c + 0x1070) == 1
            || *(short *)(c + 0x370) == 0xB))
        run = ((int (*)(int, float, float, float))ExecCharaGeometryPreprocess)(a0, (*(G *)&gcGlobalVar).f178, clip, 1.0f / clip);
    if (run != 0) {
        c = ((char * (*)(int))GetCharacterClass)(a0);
        ((void (*)(int, void *))ExecCharaGeometry)(a0, (char *)&(*(G *)&gcGlobalVar) + 0x370);
        *(char *)(c + 0x539) = StageManagerCheckAreaExist(*(int *)(((char * (*)(int))GetLayoutClass)(a0) + 0x134));
    }
    ((void (*)(int))ExecCharaGeometryPostprocess)(a0);
}

int AddDefaultAIGroup(int a, int b, int c, int d)
{
    return isysAddGroupWithLinkParam((void *)a, B_0019B868, 0, 0);
}

void *initdefaultaitask(void)
{
    isysInitGroup(B_0019B868);
    return gcCreateScriptObj(func_000965E8, 0, rootPtn, 0x1000, 0, 4, RO_0017F8D8);
}

void _initstage(void)
{
    unsigned int *ref;
    int off;
    int *t;
    char *p;

    ref = (unsigned int *)(gcGetStageData(D_0017AF5C) + 4);
    off = *ref & 0x3FFFF;
    t = off != 0 ? *(int **)((char *)ref - off) : 0;
    p = (t != 0 && t != DldSysUndefSymbol)
            ? (char *)t[4] + ((*ref >> 18) & 0xFFF) * ((int *)t[2])[3]
            : 0;
    initlayout(D_0017AF58, p, D_0017AF60, D_0017AF64, D_0017AF68, D_0017AF6C);
}

void initstage(int a0, int a1, int a2, int a3, int t0, int t1)
{
    unsigned int *ref;
    int off;
    int *t;
    char *p;

    D_0017AF5C = a1;
    D_0017AF58 = a0;
    D_0017AF60 = a2;
    D_0017AF68 = t0;
    D_0017AF6C = t1;
    D_0017AF64 = a3;
    SCR_STACK_ENTER()
    ref = (unsigned int *)(gcGetStageData(a1) + 4);
    off = *ref & 0x3FFFF;
    t = off != 0 ? *(int **)((char *)ref - off) : 0;
    p = (t != 0 && t != DldSysUndefSymbol)
            ? (char *)t[4] + ((*ref >> 18) & 0xFFF) * ((int *)t[2])[3]
            : 0;
    initlayout(D_0017AF58, p, D_0017AF60, D_0017AF64, D_0017AF68, D_0017AF6C);
    SCR_STACK_LEAVE();
}

static void func_000965E8(void)
{
    for (;;) {
        func_00096610();
        ((void (*)(void *))func_00095428)(isysGetThisSubThread());
    }
}

static void func_00096688(void)
{
    void **it;
    void *obj = 0;

    for (it = isysGroupForFirst(B_0019B868, 0); it != 0; it = isysGroupForNext(it, 0)) {
        obj = *it;
        ((void (*)(void *))execObjectWithNonTaskSwitch)(obj);
    }
    if (obj != 0)
        isysGroupForExit(obj, 0);
}
