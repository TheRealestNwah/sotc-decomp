/* NONMATCHING: 4 diffs. The no-parent branch loads chr->pos into $v1 before
 * reloading chr->dyn; the Original reloads chr->dyn first and uses $v0. */
#ifdef NONMATCHING
typedef unsigned int s128 __attribute__((mode(TI)));
typedef union {
    float f[4];
    s128 q;
} Vec4;

extern int CheckLegalCollisionGP(void *);
extern void GetGeometryPointerQuaternion(Vec4 *, void *);
extern void GetGeometryPointerPosition(Vec4 *, void *);
extern void GetCollisionDBCurrentPointOnLastPlane(Vec4 *, void *, Vec4 *);
extern s128 ZeroVector;

static inline void qconj(Vec4 *out, Vec4 *q)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "vsubw.x vf5, vf0, vf0w\n"
                         "vmulx.xyz vf11, vf11, vf5x\n"
                         "sqc2 vf11, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

static inline void qmul(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "lqc2 vf12, 0x0(%2)\n"
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
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void qnorm(Vec4 *out, Vec4 *a)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "vmul.xyzw vf15, vf14, vf14\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "vrsqrt Q, vf0w, vf15x\n"
                         "vwaitq\n"
                         "vmulq.xyzw vf15, vf14, Q\n"
                         "sqc2 vf15, 0x0(%0)\n"
                         : : "r"(out), "r"(a) : "memory");
}

static inline void sub4(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void sub3(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void scaleXYZ(Vec4 *out, Vec4 *a, float factor)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(factor) : "memory");
}

static inline void lerp4(Vec4 *out, Vec4 *a, Vec4 *b, float t)
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

static inline float length3(Vec4 *v)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(v) : "$2");
    return r;
}

static inline float squareLength3(Vec4 *p)
{
    float r;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(p) : "$2");
    return r;
}

typedef struct {
    Vec4 vel;      /* 0x00 */
    Vec4 prevVel;  /* 0x10 */
    Vec4 last;     /* 0x20 */
    Vec4 dirVel;   /* 0x30 */
    char pad40[0x48];
    float speed;   /* 0x88 */
    char pad8C[2];
    signed char parented; /* 0x8E */
} RootDyn;

typedef struct {
    char pad0[0x30];
    Vec4 pos;          /* 0x30 */
    char pad40[0x80];
    char gp[0x64];     /* 0xC0 */
    int parent;        /* 0x124 */
    char pad128[0x74];
    RootDyn *dyn;      /* 0x19C */
    char pad1A0[0x860];
    Vec4 prevQuat;     /* 0xA00 */
    Vec4 relQuat;      /* 0xA10 */
    float moved;       /* 0xA20 */
} Chr;

void func_000586C0(Chr *chr, float dt, float invdt)
{
    Vec4 q;
    Vec4 tmp;
    s128 pos;
    s128 pt;
    s128 vel;
    Vec4 *rel = &chr->relQuat;
    void *gp;
    RootDyn *dyn;
    Vec4 *prev;

    if (chr->parent != 0) {
        gp = chr->gp;
        GetGeometryPointerQuaternion(&q, gp);
        qconj(&tmp, &chr->prevQuat);
        qmul(rel, &q, &tmp);
        qnorm(rel, rel);
    } else {
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(rel) : "memory");
        gp = chr->gp;
    }
    dyn = chr->dyn;
    prev = &dyn->prevVel;
    if (chr->parent != 0) {
        int legal = CheckLegalCollisionGP(gp);
        Vec4 *a, *b;
        GetGeometryPointerPosition((Vec4 *)&pos, gp);
        prev->q = dyn->vel.q;
        if (legal) {
            GetCollisionDBCurrentPointOnLastPlane((Vec4 *)&pt, gp, (Vec4 *)&pos);
            a = (Vec4 *)&pos;
            b = (Vec4 *)&pt;
        } else {
            a = (Vec4 *)&pos;
            b = &chr->dyn->last;
        }
        sub4(&dyn->vel, a, b);
        scaleXYZ(&dyn->vel, &dyn->vel, invdt);
        if (dt < 0.033333333f) {
            lerp4(&dyn->vel, &dyn->vel, prev, dt * 30.0f);
        }
        if (chr->dyn->parented != 0) {
            float t = dt * 30.0f;
            float len;
            float s;
            sub4((Vec4 *)&vel, &dyn->vel, prev);
            scaleXYZ((Vec4 *)&vel, (Vec4 *)&vel, invdt);
            if (0.033333333f < dt) {
                chr->dyn->dirVel.q = vel;
            } else {
                lerp4(&chr->dyn->dirVel, (Vec4 *)&vel, &chr->dyn->dirVel, t);
            }
            len = length3((Vec4 *)&vel);
            if (squareLength3(&dyn->vel) >= squareLength3(prev)) {
                s = len;
            } else {
                s = -len;
            }
            if (!(0.033333333f < dt)) {
                chr->dyn->speed = s * t + chr->dyn->speed * (1.0f - t);
            } else {
                chr->dyn->speed = s;
            }
        } else {
            chr->dyn->dirVel.q = ZeroVector;
            chr->dyn->speed = 0.0f;
        }
        __asm__ __volatile__("" : : : "memory");
        chr->dyn->parented = chr->parent;
    } else {
        dyn->vel.q = chr->pos.q;
        chr->dyn->prevVel.q = chr->pos.q;
        chr->dyn->parented = chr->parent;
        chr->dyn->dirVel.q = ZeroVector;
        chr->dyn->speed = 0.0f;
    }
    if (chr->parent != 0) {
        sub3(&tmp, &chr->pos, &chr->dyn->vel);
        chr->moved = length3(&tmp);
    } else {
        chr->moved = length3(&chr->pos);
    }
}
#endif
