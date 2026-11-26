/* Parked: 28 diffs, same size. Horse control update: target tracking in the horse local frame, turn and speed limits, and the VU0 scale/normalize/apply sequences. Remaining: v0/v1 swaps in the scratch registers of the scale3 qmtc2 sequences and the 0x280/0x284 flag stores, one reordering of the 0x13C load and quaternion copy before GetQuaternionByAxisDirZX, and the final sq/swc1 store order. A 30-minute permuter run went from 440 to 350 without reducing the word diffs. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef union {
    struct { float x, y, z, w; } v;
    s128 q;
} Vec;

typedef union {
    s128 q;
    struct { char pad0[0x16]; short h16; char pad18[4]; int x1C; } s;
} Tgt;

typedef struct {
    char pad0[0x3E4];
    float x3E4;
    char pad3E8[0x400 - 0x3E8];
    float x400;
    char pad404[0x470 - 0x404];
    float quat[4];
    char pad480[0x5E4 - 0x480];
    float x5E4;
    char pad5E8[0x750 - 0x5E8];
    int x750;
    char pad754[0xCEC - 0x754];
    signed char xCEC;
} Chr;

typedef struct {
    char pad0[0x134];
    Vec *pos;
    char pad138[4];
    Vec *quat;
} Obj;

typedef struct {
    char pad0[4];
    int x4;
    int x8;
    Tgt *target;
    int x10;
    Chr *chr;
    Obj *obj;
    int *x1C;
    float mat[4][4] __attribute__((aligned(16)));
    float inv[4][4] __attribute__((aligned(16)));
    char padA0[0xA4 - 0xA0];
    float xA4;
    char padA8[4];
    float xAC;
    char padB0[0xC0 - 0xB0];
    float xC0;
    char padC4[4];
    int xC8;
    void *owner;
    Vec xD0;
    Vec xE0;
    Vec xF0;
    Vec x100;
    Vec x110;
    Vec x120;
    float x130;
    char pad134[0x144 - 0x134];
    int x144;
    char pad148[8];
    Vec x150;
    char x160[0x10];
} Tmp;

typedef struct {
    char pad0[4];
    int x4;
    char pad8[8];
    s128 x10;
    int x20;
    char pad24[0x3C - 0x24];
    int x3C;
    char pad40[0x10];
    s128 x50;
    float x60;
    char pad64[0x84 - 0x64];
    float x84;
    float x88;
    char pad8C[0xA0 - 0x8C];
    float xA0;
    float xA4;
    float xA8;
    int xAC;
    char padB0[0xD4 - 0xB0];
    int xD4;
    char padD8[8];
    s128 xE0;
    float xF0;
} Ctrl;

typedef struct { long long a, b, c, d; } Blk;

typedef struct {
    char pad0[0xE0];
    int xE0;
    char padE4[0x3CC - 0xE4];
    float x3CC;
    char pad3D0[0x10];
    union {
        Blk blk;
        struct { char pad[0x18]; float f; } s;
    } x3E0;
} Lay;

typedef struct { short pad[8]; short h10; short h12; } Line;

typedef struct {
    float m[4][4];
    float ang;
} WallParam;

typedef struct { int pad; int x4; } ScriptDef;

extern s128 fltMaxVector;
extern Vec YUnitVector;
typedef struct { char pad0[0x190]; float x190; char pad194[0x234 - 0x194]; char x234[1]; } GcGlobal;
extern GcGlobal gcGlobalVar;
extern float RO_0018156C;
extern float RO_00181570;
extern ScriptDef *ScriptCtrlDef_SCRStop;
extern int moveCtrlWallJudgeFunc();
extern void _initBaseMoveTmpWork(void *, Tmp *, Ctrl *, Lay *);
extern void func_00109028(Tmp *);
extern void SCRCharaTurnDirectInput(void *, float);
extern void analyzeMotionProperty(void *, int, float *, float *, float, float, void *);
extern void _initMovePathWork(Tmp *, void *, float);
extern int _compPassagePos(Tmp *);
extern void func_0010A738(Ctrl *);
extern Line *getLineDataByAreaIdx(Lay *, int, int);
extern void GetQuaternionByAxisDirZY(Vec *, Vec *, Vec *);
extern float getRatioFromInterp(float, float);
extern void SetObjectGeoAndUnparent(int, Vec *, Vec *);
extern void CharaCtrlSetScriptCtrlStatus(int, int);
extern void func_0010A040(Tmp *, int);
extern void func_0010A778(Vec *, Tmp *);
extern void iosCopyMatrix(void *, void *);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int, int, int, int (*)(), void *);
extern void CalcFootVec(void *, void *, void *, void *);
extern float CalcDistancePointAndLine(void *, void *, void *);
extern float iosGetCosf(float);
extern void func_00109420(void *, void *, int, int, int, Tmp *);
extern void setLockPassageWork(Lay *, int);
extern int chkAttainExecLayout(Lay *, Tgt *, Obj *, Chr *);
extern int memcmp(void *, void *, int);

static inline float vlen(void *v)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(v) : "$2");
    return r;
}

static inline float xzlen(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         ".word 0x4A2703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline void normalize3(void *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v) : "memory");
}

static inline void normalize4(void *v)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%0)\n"
                         "vmul.xyzw vf15, vf14, vf14\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "vrsqrt Q, vf0w, vf15x\n"
                         "vwaitq\n"
                         "vmulq.xyzw vf15, vf14, Q\n"
                         "sqc2 vf15, 0x0(%0)\n"
                         : : "r"(v) : "memory");
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

static inline void vadd3(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
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

static inline float dot4(Vec *a, Vec *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x0(%2)\n"
                         "vmul.xyzw vf15, vf14, vf15\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "qmfc2.ni %0, vf15\n"
                         : "=r"(r) : "r"(a), "r"(b));
    return r;
}

static inline void negate4(Vec *v)
{
    float m = -1.0f;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v), "r"(m) : "memory");
}

static inline void lerp4(Vec *out, Vec *a, Vec *b, float t)
{
    __asm__ __volatile__("mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyzw ACC, vf5, vf7x\n"
                         "vmaddw.xyzw vf9, vf6, vf8w\n"
                         "sqc2 vf9, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b), "f"(t) : "$8", "memory");
}

static inline void blend4(Vec *out, Vec *b, Vec *a, float t)
{
    float dsign;
    dsign = dot4(a, b);
    __asm__("" : "+m"(dsign));
    if (*(int *)&dsign < 0)
        negate4(b);
    lerp4(out, a, b, t);
    normalize4(out);
}

void updateHorseCtrlWork(void *th, Ctrl *ctrl, Lay *lay)
{
    Tmp w;
    union {
        struct { Vec a; Vec b; } v;
        Blk save;
    } u;
    Vec c;
    Vec d;
    Vec e;
    char hit[0x40] __attribute__((aligned(16)));
    Vec fv;
    WallParam jp __attribute__((aligned(16)));
    float r0;
    float r1;
    int flag;
    int ok;
    Vec *dir;
    Tmp *p = &w;
    Tmp *q = &w;
#define a u.v.a
#define b u.v.b

    _initBaseMoveTmpWork(th, p, ctrl, lay);
    {
        register float *m __asm__("$2") = w.inv[0];
        quatToMatrix(m, w.chr->quat);
        m += 12;
        unitRow(m);
    }
    matInverse(q->mat[0], q->inv[0]);
    p->owner = ctrl;
    func_00109028(p);
    q->chr->x5E4 = 1.0f;
    SCRCharaTurnDirectInput(th, 0.0f);
    analyzeMotionProperty(th, *q->x1C, &r0, &r1, 1.0f, 0.0f, p->x160);
    ctrl->xF0 = r0 / r1 * q->xAC;
    _initMovePathWork(p, &p->xC0, ctrl->x84);
    if (ctrl->xAC != 0 && ctrl->xAC != *p->x1C)
        ctrl->xAC = 0;
    if (_compPassagePos(p) != 0) {
        ctrl->x10 = p->target->q;
        func_0010A738(ctrl);
    }
    if (ctrl->x60 == RO_0018156C)
        ctrl->x60 = p->x130;
    if (ctrl->x4 == 0) {
        ctrl->x10 = fltMaxVector;
        func_0010A738(ctrl);
        return;
    }
    if (ctrl->x3C != 0)
        return;
    if (p->chr->xCEC == 0) {
        Line *ld;
        Obj *obj;
        float t;

        if (p->target == 0)
            return;
        ld = getLineDataByAreaIdx(lay, p->target->s.h16, p->target->s.x1C);
        if (ld != 0 && (ld->h10 == 0x200 || ld->h12 == 0x200))
            return;
        vsub(&a, p->target, p->obj->pos);
        normalize3(&a);
        d.q = a.q;
        d.v.y = 0.0f;
        GetQuaternionByAxisDirZY(&c, &d, &YUnitVector);
        obj = p->obj;
        t = getRatioFromInterp(1.0f, gcGlobalVar.x190);
        e.q = obj->quat->q;
        blend4(&c, &e, &c, t);
        scale3(&a, &a, ctrl->x88 * gcGlobalVar.x190);
        vadd3(&b, &a, p->obj->pos);
        b.v.w = 1.0f;
        SetObjectGeoAndUnparent(p->x8, &c, &b);
        CharaCtrlSetScriptCtrlStatus(p->x8, ScriptCtrlDef_SCRStop->x4);
        return;
    }
    if (p->target == 0)
        return;
    if (p->x10 != 0) {
        float dist;
        float f21;
        float xl;
        float dt;
        int a3;

        if (!(0.0f < p->xA4)) {
            func_0010A040(p, 0);
            return;
        }
        flag = 0;
        func_0010A778(&a, p);
        ok = 1;
        matVec(&b, p->inv, &a);
        jp.ang = p->chr->x400 * 57.29578f;
        iosCopyMatrix(jp.m, p->mat);
        if (ClipCollisionDirectCallBack(hit, p->obj->pos, &b, gcGlobalVar.x234, 0, 0, 0, moveCtrlWallJudgeFunc, &jp)) {
            float len;

            matVec(&a, p->mat, &fv);
            dir = &p->xD0;
            CalcFootVec(&c, &a, &p->x100, dir);
            len = vlen(&c);
            if (p->chr->x3E4 <= len) {
                normalize3(&c);
                scale3(&c, &c, len - p->chr->x3E4);
                vadd(&a, &a, &c);
                a.v.w = 1.0f;
            } else {
                ok = 0;
                a.q = p->x100.q;
            }
            matVec(&b, p->inv, &a);
        } else {
            dir = &p->xD0;
        }
        if (ok) {
            if (ctrl->xD4 == 0) {
                dist = CalcDistancePointAndLine(&a, &p->x100, dir);
                if (dist <= p->xC0) {
                    if (ctrl->xA4 < ctrl->xF0) {
                        ctrl->xA4 = ctrl->xF0;
                        ctrl->xE0 = b.q;
                    } else {
                        b.q = ctrl->xE0;
                        matVec(&a, p->mat, &b);
                    }
                    if (ctrl->xA0 < p->xAC)
                        ctrl->xA0 = p->xAC;
                    ctrl->xA8 = 0;
                } else {
                    f21 = ctrl->xA4;
                    if (f21 == RO_00181570) {
                        CalcFootVec(&c, &a, &p->x100, dir);
                        scale3(&c, &c, (dist - p->xC0) / dist);
                        vadd(&a, &a, &c);
                        a.v.w = 1.0f;
                        matVec(&b, p->inv, &a);
                        flag = 1;
                        ctrl->xE0 = b.q;
                    } else {
                        b.q = ctrl->xE0;
                        matVec(&a, p->mat, &b);
                        if (f21 < ctrl->xF0) {
                            float f2 = ctrl->xF0;
                            float f1 = ctrl->xA8;
                            float lim;
                            lim = f2 * f1 + (f21 - f2) / f1 * 0.5f * f1 * f1;

                            if (xzlen(&b, p->obj->pos) < lim * (dist = 1.05f)) {
                                vsub(&d, &p->x120, &b);
                                vsub(&e, &b, p->obj->pos);
                                d.v.y = 0.0f;
                                e.v.y = 0.0f;
                                normalize3(&d);
                                normalize3(&e);
                                if (iosGetCosf(0.52359879f) > dot3(&d, &e)) {
                                    if (ctrl->xA0 < p->xAC * dist || 1.25f * f21 < ctrl->xF0)
                                        flag = 1;
                                }
                            }
                        }
                    }
                }
            } else {
                b.q = ctrl->xE0;
                matVec(&a, p->mat, &b);
            }
        }
        vsub(&c, &a, &p->x110);
        c.v.y = 0.0f;
        normalize3(&c);
        xl = xzlen(&b, p->obj->pos);
        dt = dot3(&c, dir);
        a3 = ctrl->xD4;
        if (a3 != 0 || xl < lay->x3CC || dt <= 0.0f || xl < ctrl->xF0 * 0.16666666f || !ok) {
            if (ok && (xl < lay->x3CC || dt <= 0.0f)) {
                ctrl->xD4 = 1;
                a3 = 1;
            }
            if (p->xC8 == 0)
                func_00109420(&p->x100, &p->xE0, flag, a3, 0, p);
            else
                func_00109420(&p->x100, &p->xF0, flag, a3, 0, p);
        } else {
            func_00109420(&a, dir, 0, 0, 0, p);
        }
    } else {
        u.save = lay->x3E0.blk;

        if (lay->xE0 == 0) {
            setLockPassageWork(lay, 1);
            if (0.087266465f < lay->x3E0.s.f)
                lay->x3E0.s.f = 0.087266465f;
        } else {
            setLockPassageWork(lay, 0);
        }
        if (p->chr->x750 == ctrl->x20 && chkAttainExecLayout(lay, p->target, p->obj, p->chr) == 1) {
            setLockPassageWork(lay, 0);
        } else if (0.0f < p->xA4) {
            if (p->x144 != 0) {
                matVec(&c, p->mat, &p->x150);
                c.v.y = 0.0f;
                normalize3(&c);
                func_00109420(&p->x100, &c, 0, 0, 1, p);
            } else {
                func_00109420(&p->x100, &p->xD0, 0, 0, 1, p);
            }
        } else {
            if (memcmp(&ctrl->x50, p->target, 0xC) != 0) {
                ctrl->x50 = p->target->q;
                ctrl->x60 = p->x130;
            }
            func_0010A040(p, 1);
        }
        if (lay->xE0 == 0)
            lay->x3E0.blk = u.save;
    }
}
#endif
