#ifdef NONMATCHING /* 2 diffs */
typedef int s128 __attribute__((mode(TI)));

typedef union {
    struct { float x, y, z, w; } v;
    s128 q;
} Vec;

typedef struct {
    char pad0[0x35D];
    signed char x35D;
    char pad35E[0x400 - 0x35E];
    float x400;
    char pad404[0x750 - 0x404];
    int x750;
} Chr;

typedef struct {
    char pad0[0x134];
    Vec *pos;
    char pad138[4];
    float *quat;
} Obj;

typedef struct {
    char pad0[4];
    int x4;
    int x8;
    s128 *target;
    int x10;
    Chr *chr;
    Obj *obj;
    char pad1C[4];
    float mat[4][4] __attribute__((aligned(16)));
    float inv[4][4] __attribute__((aligned(16)));
    char padA0[0xC0 - 0xA0];
    float xC0;
    char padC4[4];
    int xC8;
    void *owner;
    Vec xD0;
    Vec xE0;
    Vec xF0;
    Vec x100;
    Vec x110;
    char pad120[0x10];
    float x130;
    char pad134[0x164 - 0x134];
    int x164;
    int x168;
    char pad16C[4];
} Tmp;

typedef struct {
    char pad0[4];
    int x4;
    char pad8[8];
    s128 x10;
    int x20;
    char pad24[0xC];
    int x30;
    float x34;
    char pad38[8];
    Vec x40;
    int x50;
    float x54;
    char pad58[0x6C - 0x58];
    float x6C;
    char pad70[0x10];
    int x80;
    int x84;
    char pad88[0x9C - 0x88];
    float x9C;
    char padA0[0xD4 - 0xA0];
    int xD4;
    char padD8[0xE8 - 0xD8];
    int xE8;
} Ctrl;

typedef struct {
    char pad0[0xA8];
    int xA8;
    char padAC[4];
    Vec xB0;
    char padC0[0xE0 - 0xC0];
    int xE0;
    char padE4[0x3CC - 0xE4];
    float x3CC;
} Lay;

typedef struct { int pad; int x4; } ScriptDef;

extern s128 fltMaxVector;
extern Vec YUnitVector;
typedef struct { char pad0[0x190]; float x190; char pad194[0x238 - 0x194]; char x238[1]; } GcGlobal;
extern GcGlobal gcGlobalVar;
extern float RO_00181634;
extern ScriptDef *ScriptCtrlDef_SCRAccel;
extern int coliJudgeNotWater();
extern char *GetLayoutClass(void *);
extern void _initBaseMoveTmpWork(void *, Tmp *, Ctrl *, Lay *);
extern void iosInverseMatrix(void *, void *);
extern float getRatioFromInterp(float, float);
extern void func_001106D0(Tmp *);
extern void _initMovePathWork(Tmp *, void *, float);
extern int _compPassagePos(Tmp *);
extern void func_00113078(Ctrl *);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, void *, int, int, void *, int);
extern Vec *GetGeometryPointerSurfacePlane(void *);
extern float iosGetCosf(float);
extern void CharaCtrlSetScriptCtrlStatus(int, int);
extern int func_00110A88(void *, Tmp *);
extern float CalcDistancePointAndLine(void *, void *, void *);
extern void CalcFootVec(void *, void *, void *, void *);
extern void func_00112B08(Tmp *, void *);
extern void func_00111218(void *, void *, int, Tmp *);
extern int setLockPassageWork(int, int);
extern int chkAttainExecLayout(Lay *, s128 *, Obj *, Chr *);
extern int chkAttainExecColumn(Lay *, s128 *, Obj *, Chr *);
extern void forceSetWayFinish(Lay *);
extern void func_00110DD8(Tmp *);

static inline float vlen(void *v)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(v) : "$2");
    return r;
}

static inline void quatToMatrix(float *out, float *quat)
{
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%1)\n"
                         "vmr32.w vf14, vf0\n"
                         "vmr32.w vf15, vf0\n"
                         "vmr32.w vf16, vf0\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf0, vf0\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf0, vf0\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         : : "r"(out), "r"(quat));
}

static inline void unitRow(float *out)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(out));
}

static inline void matInverse(float *dst, float *src)
{
    __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq $8, 0x0(%1)\n"
                         "lq $9, 0x10(%1)\n"
                         "lq $10, 0x20(%1)\n"
                         "qmfc2.ni $11, vf0\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "pcpyud $11, $13, $15\n"
                         "qmtc2.ni $8, vf24\n"
                         "qmtc2.ni $9, vf25\n"
                         "qmtc2.ni $10, vf26\n"
                         "vmulax.xyzw ACC, vf24, vf28x\n"
                         "vmadday.xyzw ACC, vf25, vf28y\n"
                         "vmaddaz.xyzw ACC, vf26, vf28z\n"
                         "vmaddw.xyzw vf29, vf0, vf28w\n"
                         "vsub.w vf29, vf29, vf29\n"
                         "vadd.w vf29, vf29, vf0\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf29, 0x30(%0)\n"
                         : : "r"(dst), "r"(src) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}

static inline void scaleW(void *d, void *a, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(s) : "memory");
}

static inline void scale3(void *d, void *a, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(s) : "memory");
}

static inline void vadd(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vsub(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline float dot3(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline void matVec(void *d, void *m, void *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(d), "r"(m), "r"(v) : "memory");
}

void updateWormCtrlWork(void *th, Ctrl *ctrl, Lay *lay)
{
    Tmp w;
    Tmp *p = &w;
    Tmp *b = &w;
    union {
        struct { char hit[0x50]; Vec v; } a;
        struct { Vec pos; Vec l; Vec fv; } b;
        Vec t;
    } u;

    ctrl->x9C = vlen(GetLayoutClass(th) + 0x30);
    _initBaseMoveTmpWork(th, p, ctrl, lay);
    p->owner = ctrl;
    do {
    {
        register float *m __asm__("$3") = w.mat[0];
        quatToMatrix(m, w.obj->quat);
        m += 12;
        unitRow(m);
    }
    matInverse(b->mat[0], b->mat[0]);
    iosInverseMatrix(b->inv, b->mat);
    p->x130 = getRatioFromInterp(ctrl->x6C, gcGlobalVar.x190);
    func_001106D0(p);
    _initMovePathWork(p, &p->xC0, ctrl->x54);
    ctrl->xE8 = 0;
    if (_compPassagePos(p) != 0) {
        ctrl->x10 = *p->target;
        func_00113078(ctrl);
    }
    p->x168 = 0;
    } while (0);
    ctrl->xD4 = 0;
    if (p->chr->x750 == ctrl->x80 || p->chr->x750 == ctrl->x84) {
        scaleW(&u.a.v, &YUnitVector, 100.0f);
        vadd(&u.a.v, &u.a.v, p->obj->pos);
        u.a.v.v.w = 1.0f;
        if (ClipCollisionDirectCallBack(u.a.hit, &u.a.v, p->obj->pos, gcGlobalVar.x238, 0, 0, 0, coliJudgeNotWater, 0) == 0) {
            ctrl->xD4 = 0;
        } else {
            Vec *n = GetGeometryPointerSurfacePlane(u.a.hit);
            if (iosGetCosf(p->chr->x400) <= dot3(n, &YUnitVector))
                ctrl->xD4 = 1;
            else
                ctrl->xD4 = 0;
        }
        if (ctrl->xD4 != 0 || p->chr->x35D != 0)
            p->x168 = 1;
    }
    if (ctrl->x4 == 0) {
        ctrl->x10 = fltMaxVector;
    } else if (p->x168 == 0 && p->target != 0) {
        if (p->x10 != 0) {
            if (p->chr->x750 == ctrl->x20) {
                CharaCtrlSetScriptCtrlStatus(p->x8, ScriptCtrlDef_SCRAccel->x4);
            } else {
                int ok = func_00110A88(&u.b.pos, p);
                float d, len, dt;
                matVec(&u.b.l, p->inv, &u.b.pos);
                if (ctrl->x30 == 0) {
                    d = CalcDistancePointAndLine(&u.b.pos, &p->x100, &p->xD0);
                    if (d <= p->xC0 && ctrl->x34 < d && ok) {
                        ctrl->x34 = d;
                        ctrl->x40.q = u.b.l.q;
                    } else if (ctrl->x40.v.x != RO_00181634) {
                        u.b.l.q = ctrl->x40.q;
                        matVec(&u.b.pos, p->mat, &u.b.l);
                    } else {
                        if (ok) {
                            CalcFootVec(&u.b.fv, &u.b.pos, &p->x100, &p->xD0);
                            scale3(&u.b.fv, &u.b.fv, (d - p->xC0) / d);
                            vadd(&u.b.pos, &u.b.pos, &u.b.fv);
                            u.b.pos.v.w = 1.0f;
                        }
                        matVec(&u.b.l, p->inv, &u.b.pos);
                        ctrl->x40.q = u.b.l.q;
                    }
                } else {
                    u.b.l.q = ctrl->x40.q;
                    matVec(&u.b.pos, p->mat, &u.b.l);
                }
                vsub(&u.b.fv, &u.b.pos, &p->x110);
                len = vlen(&u.b.fv);
                scale3(&u.b.fv, &u.b.fv, 1.0f / len);
                dt = dot3(&u.b.fv, &p->xD0);
                if (ctrl->x30 != 0 || len < *(float *)((char *)lay + 0x3CC) || dt <= 0.0f) {
                    ctrl->x30 = 1;
                    if (p->xC8 == 0)
                        func_00111218(&p->x100, &p->xE0, 0, p);
                    else
                        func_00111218(&p->x100, &p->xF0, 0, p);
                } else {
                    func_00112B08(p, &u.b.pos);
                }
            }
        } else {
            int r;
            if (lay->xE0 == 0)
                setLockPassageWork(p->x4, 1);
            else
                setLockPassageWork(p->x4, 0);
            r = chkAttainExecLayout(lay, p->target, p->obj, p->chr);
            if (r == 1)
                ctrl->x50 = r;
            if (p->chr->x750 == ctrl->x20) {
                if (ctrl->x50 == 0)
                    CharaCtrlSetScriptCtrlStatus(p->x8, ScriptCtrlDef_SCRAccel->x4);
            } else if (p->x164 == 0) {
                if (lay->xA8 != 0) {
                    matVec(&u.t, p->mat, &lay->xB0);
                    func_00111218(&p->x100, &u.t, 1, p);
                } else {
                    func_00112B08(p, &p->x100);
                }
            } else {
                func_00111218(&p->x100, &p->xD0, 1, p);
            }
            if (lay->xE0 == 0 && p->chr->x750 == ctrl->x20) {
                setLockPassageWork(p->x4, 0);
                if (ctrl->x50 != 0 || chkAttainExecColumn(lay, p->target, p->obj, p->chr) != 0)
                    forceSetWayFinish(lay);
            }
        }
    }
    func_00110DD8(p);
}
#endif
