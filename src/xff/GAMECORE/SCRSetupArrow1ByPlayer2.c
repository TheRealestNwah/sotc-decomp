typedef int s128 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } Vec __attribute__((aligned(16)));

typedef struct ArrowNode {
    char pad0[0x30];
    s128 dir30;
    int f40;
    float f44;
    int f48;
    int f4C;
    char pad50[0x40];
    void *obj90;
    void *obj94;
    int f98;
    int f9C;
    short fA0;
    short fA2;
    short fA4;
    short fA6;
    short fA8;
    short fAA;
    char padAC[4];
    float fB0;
    int fB4;
    int fB8;
    int fBC;
    struct ArrowNode *next;
} ArrowNode;

typedef struct {
    int count;
    ArrowNode *head;
    ArrowNode *tail;
} ArrowList;

typedef struct {
    char pad[0x1450];
    ArrowList used;
    ArrowList free;
} ArrowPool;

typedef struct {
    int a30;
    Vec *pos;
    void *rot;
    int a3C, a40, a44, a48, a4C, a50, a54, a58, a5C, a60, a64, a68;
} LayoutInit;

extern ArrowPool B_001889A0;
extern ArrowList B_00189DF0;
extern ArrowList B_00189DFC;
extern s128 YUnitVector;
extern s128 ZeroPoint;
extern s128 IdentityQuaternion;
extern char RO_0017CF98[];
extern int D_0017A978;
extern int LayoutObjDef_BASE_ARROW;
extern int LayoutObjDef_BASE_EXPARROW;
extern int LayoutObjDef_BASE_HARPOON;
extern int LayoutObjDef_BASE_SOUNDARROW;
extern float *ScrParam_bow_speed, *ScrParam_bow_range;
extern float *ScrParam_bombbow_speed, *ScrParam_bombbow_range;
extern float *ScrParam_harpoon_speed, *ScrParam_harpoon_range;
extern int ScriptAnimationObjDef_ARROW_SHOOT;
extern int ScriptAnimationObjDef_ARROW_EXP_SHOOT;
extern int ScriptAnimationObjDef_ARROW_SOUND_SHOOT;
extern int ScriptAnimationObjDef_HARPOON_SHOOT;
extern char gcGlobalVar[];
extern void GetQuaternionByAxisDirZY(void *, Vec *, s128 *);
extern void func_000317C8(ArrowNode *);
extern void *initLayoutObj(void *, int, int, LayoutInit *);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
extern void SetLayoutObjSubDispFunc(void *, void *, void *);
extern char *GetLayoutClass(void *);
extern float getNowPowerRatio(void);
extern void resetAttackPower(void);
extern void SetGeometryPointerNodePosState(void *, void *, int, s128 *, s128 *);
extern void *_SCRSetupLWS(int, void *, s128 *, s128 *, int);
extern void _SCRStartLWS(void *, int, int, void *);
extern void SetScriptObjDeleteCallBackFunc(void *, void *, void *);
extern void func_00033680();
extern void func_00034970();

static inline int arrowListRemove(ArrowList *l, ArrowNode *n)
{
    ArrowNode *p;
    ArrowNode *prev;

    if (l->head != 0) {
        p = l->head;
        prev = 0;
        for (; p != 0; p = p->next) {
            if (p == n) {
                if (prev != 0)
                    prev->next = n->next;
                if (l->head == n)
                    l->head = n->next;
                if (l->tail == n)
                    l->tail = prev;
                l->count--;
                return 1;
            }
            prev = p;
        }
    }
    return 0;
}

static inline void arrowListAppend(ArrowList *l, ArrowNode *n)
{
    if (n != 0) {
        if (l->tail != 0)
            l->tail->next = n;
        else
            l->head = n;
        *(int *)&n->next = 0;
        l->tail = n;
        l->count++;
    }
}

static inline ArrowNode *arrowAlloc(ArrowPool *pool)
{
    ArrowNode *n = pool->free.head;

    if (n != 0 && arrowListRemove(&pool->free, n)) {
        arrowListAppend(&B_00189DF0, n);
        return n;
    }
    return 0;
}

static inline void quatToDir(Vec *out, Vec *q)
{
    __asm__ __volatile__("lqc2        vf4, 0x0(%1)\n"
                         "vmul.xyzw   vf5, vf4, vf4\n"
                         "vmr32.xyzw  vf6, vf4\n"
                         "vmul.xyzw   vf7, vf6, vf4\n"
                         "vmr32.xyzw  vf6, vf6\n"
                         "vmul.xyzw   vf8, vf6, vf4\n"
                         "vsubx.z     vf6, vf0, vf5x\n"
                         "vsuby.z     vf6, vf6, vf5y\n"
                         "vaddw.y     vf6, vf7, vf7w\n"
                         "vsuby.x     vf6, vf8, vf8y\n"
                         "vsub.w      vf6, vf0, vf0\n"
                         "vadd.w      vf5, vf0, vf0\n"
                         "vmulw.xyz   vf6, vf6, vf5w\n"
                         "vaddw.z     vf6, vf6, vf0w\n"
                         "sqc2        vf6, 0x0(%0)\n"
                         :
                         : "r"(out), "r"(q)
                         : "memory");
}

void SCRSetupArrow1ByPlayer2(int unused, int type, Vec *dir, Vec *pos)
{
    Vec rot;
    Vec p;
    Vec d;
    LayoutInit li;
    Vec v;
    Vec gp[4];
    ArrowNode *n;
    ArrowPool *pool;
    char *lc;
    void *q;
    int def;
    float *speed;
    float *range;
    float sp, rg;
    float r1, r2;

    *(s128 *)&d = *(s128 *)dir;
    GetQuaternionByAxisDirZY(&rot, &d, &YUnitVector);
    pool = &B_001889A0;
    *(s128 *)&p = *(s128 *)pos;
    __asm__ __volatile__("" : : "r"(pool));
    n = arrowAlloc(pool);
    if (n == 0) {
        func_000317C8(B_001889A0.used.head);
        n = arrowAlloc(&B_001889A0);
    }
    li.pos = &p;
    li.a30 = 0;
    li.rot = &rot;
    li.a3C = 0;
    li.a50 = 0;
    li.a40 = 0;
    li.a44 = 0;
    li.a48 = 0;
    li.a4C = 1;
    li.a5C = 1;
    li.a54 = 0;
    li.a58 = 0;
    li.a60 = 0;
    li.a64 = 0;
    li.a68 = 0;
    switch (type) {
    case 4:
        n->obj94 = initLayoutObj(RO_0017CF98, D_0017A978, LayoutObjDef_BASE_ARROW, &li);
        break;
    case 7:
        n->obj94 = initLayoutObj(RO_0017CF98, D_0017A978, LayoutObjDef_BASE_EXPARROW, &li);
        break;
    case 6:
        n->obj94 = initLayoutObj(RO_0017CF98, D_0017A978, LayoutObjDef_BASE_SOUNDARROW, &li);
        break;
    case 5:
        n->obj94 = initLayoutObj(RO_0017CF98, D_0017A978, LayoutObjDef_BASE_HARPOON, &li);
        break;
    }
    if (n->obj94 == 0) {
        if (n != 0 && arrowListRemove(&B_00189DF0, n)) {
            arrowListAppend(&B_00189DFC, n);
            n->obj94 = 0;
        }
        return;
    }
    isysAddGroupWithLinkParam(n->obj94, gcGlobalVar + 0x280, 0, 0);
    SetLayoutObjSubDispFunc(n->obj94, func_00033680, n);
    lc = GetLayoutClass(n->obj94);
    n->f48 = type;
    n->f4C = -1;
    n->f40 = 0;
    n->fA0 = 0;
    n->fA2 = 1;
    n->fAA = 1;
    n->f9C = 0;
    n->fA4 = 0;
    n->fA6 = 0;
    n->fB4 = 0;
    n->fB8 = 0;
    n->fBC = 0;
    n->fA8 = 0;
    n->f98 = 0;
    if (getNowPowerRatio() > 1.0f) {
        n->fB0 = getNowPowerRatio();
    } else {
        r1 = getNowPowerRatio();
        r2 = getNowPowerRatio();
        n->fB0 = r1 * r2 * getNowPowerRatio();
    }
    resetAttackPower();
    q = &v;
    sp = 0.0f;
    n->f44 = sp;
    rg = sp;
    __asm__ __volatile__("" : : : "memory");
    quatToDir(q, *(Vec **)(lc + 0x13C));
    switch (n->f48) {
    case 4:
    case 6:
        sp = ScrParam_bow_speed[1];
        rg = ScrParam_bow_range[1];
        break;
    case 7:
        sp = ScrParam_bombbow_speed[1];
        rg = ScrParam_bombbow_range[1];
        break;
    case 5:
        sp = ScrParam_harpoon_speed[1];
        rg = ScrParam_harpoon_range[1];
        break;
    }
    if (sp != 0.0f)
        n->f44 = rg / (sp / 3.6f);
    __asm__ __volatile__("lqc2        vf5, 0x0(%1)\n"
                         "qmtc2.ni    %2, vf6\n"
                         "vmulx.xyz   vf5, vf5, vf6x\n"
                         "sqc2        vf5, 0x0(%0)\n"
                         :
                         : "r"(&n->dir30), "r"(&v), "r"(sp * 1000.0f / 3600.0f)
                         : "memory");
    SetGeometryPointerNodePosState(gp, n->obj94, 0, &IdentityQuaternion, &ZeroPoint);
    n->obj90 = 0;
    switch (n->f48) {
    case 4:
        n->obj90 = _SCRSetupLWS(ScriptAnimationObjDef_ARROW_SHOOT, gp, &ZeroPoint, &IdentityQuaternion, 0);
        break;
    case 7:
        n->obj90 = _SCRSetupLWS(ScriptAnimationObjDef_ARROW_EXP_SHOOT, gp, &ZeroPoint, &IdentityQuaternion, 0);
        break;
    case 6:
        n->obj90 = _SCRSetupLWS(ScriptAnimationObjDef_ARROW_SOUND_SHOOT, gp, &ZeroPoint, &IdentityQuaternion, 0);
        break;
    case 5:
        n->obj90 = _SCRSetupLWS(ScriptAnimationObjDef_HARPOON_SHOOT, gp, &ZeroPoint, &IdentityQuaternion, 0);
        break;
    }
    if (n->obj90 != 0) {
        _SCRStartLWS(n->obj90, -1, 5, &n->f9C);
        SetScriptObjDeleteCallBackFunc(n->obj90, func_00034970, n);
    }
}
