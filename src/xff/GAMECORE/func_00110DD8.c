/* Worm control velocity step: integrates the vertical speed (+0x98/+0x9C) with the accel/brake values of the worm param while the object is in one of its two states, moves a free-root object along Y, then slerps the root quaternion toward identity, advances along its local Y axis and eases the height to the target when type 4 is grounded. */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0x190];
    float dt;
} GV;

typedef struct {
    char pad0[0x134];
    Vec4 *pos;
    char pad138[0x13C - 0x138];
    Vec4 *rot;
} Layout;

typedef struct {
    char pad0[0x80];
    int id0;
    int id1;
    float a88;
    float a8C;
    float a90;
    float a94;
    float vel;
    float spd;
    Vec4 quat;
    char padB0[0xB4 - 0xB0];
    float fB4;
    char padB8[0xBC - 0xB8];
    int type;
    float targetY;
    char padC4[0xC8 - 0xC4];
    int snap;
    char padCC[0xD4 - 0xCC];
    int fD4;
} WormParam;

typedef union { char *obj; float f; } ObjU;
typedef struct {
    char pad0[0x14];
    ObjU u;
    Layout *lay;
    char pad1C[0xCC - 0x1C];
    WormParam *p;
    char padD0[0x154 - 0xD0];
    float f154;
    char pad158[0x168 - 0x158];
    int f168;
} WormWork;

extern GV gcGlobalVar;
extern int MotRootDyn_NOROOTDYNAMICS_POS_FREE;
extern s128 YUnitVector;
extern s128 IdentityQuaternion;
extern float getValueInterp(float, float, float, float);

static inline void scale4(void *out, void *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline void scale3(void *out, void *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline void add3(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float dot4(Vec4 *a, Vec4 *b)
{
    register float r __asm__("$f0");
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

static inline void lerpNorm(Vec4 *out, Vec4 *a, Vec4 *b, float t)
{
    __asm__ __volatile__("mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyzw ACC, vf5, vf7x\n"
                         "vmaddw.xyzw vf9, vf6, vf8w\n"
                         "sqc2 vf9, 0x0(%0)\n"
                         "lqc2 vf14, 0x0(%0)\n"
                         "vmul.xyzw vf15, vf14, vf14\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "vrsqrt Q, vf0w, vf15x\n"
                         "vwaitq\n"
                         "vmulq.xyzw vf15, vf14, Q\n"
                         "sqc2 vf15, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b), "f"(t) : "$8", "memory");
}

static inline void slerp(Vec4 *b, Vec4 *out, Vec4 *a, float t)
{
    float d;
    *(volatile float *)&d = dot4(a, b);
    if (*(volatile int *)&d < 0)
        scale4(b, b, -1.0f);
    lerpNorm(out, a, b, t);
}

static inline void quatMul(Vec4 *out, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
                         "lqc2 vf12, 0x0(%1)\n"
                         "vmul.xyzw vf13, vf11, vf12\n"
                         "vaddy.x vf13, vf13, vf13y\n"
                         "vaddz.x vf13, vf13, vf13z\n"
                         "vsubx.w vf13, vf13, vf13x\n"
                         "vmulw.xyz vf14, vf12, vf11w\n"
                         "vmulw.xyz vf15, vf11, vf12w\n"
                         "vopmula.xyz ACC, vf12, vf11\n"
                         "vopmsub.xyz vf16, vf11, vf12\n"
                         "vadd.xyz vf13, vf14, vf15\n"
                         "vadd.xyz vf13, vf13, vf16\n"
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(out), "r"(b) : "memory");
}

static inline void norm4(Vec4 *v)
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

static inline void quatAxisY(void *out, void *q)
{
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
                         : : "r"(out), "r"(q) : "memory");
}

static void func_00110DD8(WormWork *w)
{
    struct {
        Vec4 r;
        Vec4 q;
    } L __attribute__((aligned(16)));
    WormParam *p;
    int id;
    float y;

    p = w->p;
    id = *(int *)(w->u.obj + 0x750);
    if (id == p->id0 || id == p->id1) {
        if (p->fD4 == 0) {
            if (w->f168 != 0) {
                if (0.0f < p->spd && p->a90 < 0.0f)
                    p->vel = p->vel + p->a90 * gcGlobalVar.dt;
            } else {
                if (p->a8C > p->fB4)
                    p->fB4 = p->fB4 + __builtin_fabsf(p->a88) * gcGlobalVar.dt;
            }
            if (0.0f <= p->a90) {
                p->vel = 0.0f;
                p->spd = 0.0f;
            }
            if (MotRootDyn_NOROOTDYNAMICS_POS_FREE == *(int *)(w->u.obj + 0x510)) {
                scale4(&L.r, &YUnitVector, -p->fB4 * gcGlobalVar.dt);
                add3(w->lay->pos, w->lay->pos, &L.r);
            }
        } else {
            if (0.0f <= p->a94) {
                p->vel = 0.0f;
                p->spd = 0.0f;
            } else if (0.0f < p->spd) {
                p->vel = p->vel + p->a94 * gcGlobalVar.dt;
            }
        }
    }
    p->spd = p->spd + p->vel * gcGlobalVar.dt;
    if (p->spd <= 0.0f) {
        p->spd = 0.0f;
        if (p->vel < 0.0f)
            p->vel = 0.0f;
    }
    if (MotRootDyn_NOROOTDYNAMICS_POS_FREE == *(int *)(w->u.obj + 0x510)) {
        L.q.q = IdentityQuaternion;
        slerp(&L.q, &L.r, &p->quat, gcGlobalVar.dt);
        quatMul(w->lay->rot, &L.r);
        norm4(w->lay->rot);
        y = w->lay->pos->f[1];
        quatAxisY(&L.q, w->lay->rot);
        scale3(&L.q, &L.q, p->spd * gcGlobalVar.dt);
        add3(w->lay->pos, w->lay->pos, &L.q);
        w->lay->pos->f[3] = 1.0f;
        if (p->type == 4) {
            if (__builtin_fabsf(w->f154) < 0.17453293f &&
                __builtin_fabsf(w->lay->pos->f[1] - p->targetY) < 2.0f)
                p->snap = 1;
            if (p->snap)
                w->lay->pos->f[1] = getValueInterp(y, p->targetY, 5.0f, gcGlobalVar.dt);
        }
    }
}

