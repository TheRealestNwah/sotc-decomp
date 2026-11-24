/* Parked attempt, 1 diff, same size. Builds a camera frame from the direction to the target, finds where the circle of radius r around the start is tangent to the target, and fills the A3/B3/C3 acceleration work area at w. The two addresses are pinned to $s1/$s0 with an empty asm between them so w+0x20 is computed first, as in the Original. Remaining: the A3 call's last argument (w+n, kept for the argument order) is recomputed with addiu instead of reusing $s1. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { char pad[0x190]; float dt; } GcGlobal;

extern GcGlobal gcGlobalVar;
extern Vec4 ZeroVector;
extern Vec4 ZeroPoint;
extern Vec4 XUnitVectorInv;
extern void *memset(void *, int, int);
extern void iosSetCameraMatrix(void *, void *, void *, void *);
extern int AI_CalcIntersectionCircleXZ(Vec4 *, Vec4 *, Vec4 *, Vec4 *, float, float);
extern float iosGetACosfExact(float);
extern void AI_GetAccelA3XYZ(void *, void *, void *, void *, void *, void *, float);
extern void AI_GetAccelB3XYZ(void *, void *, void *, void *, void *, void *, float);
extern void AI_GetAccelC3XYZ(void *, void *, void *, void *, void *, void *, float);

#define F(p, o) (*(float *)((char *)(p) + (o)))
#define Q(p, o) (*(s128 *)((char *)(p) + (o)))

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

static inline void vsub3(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vadd3(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float vlen(void *v)
{
    float d;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(v) : "$2", "memory");
    return d;
}

static inline void vscale4(void *out, void *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(v), "r"(s) : "memory");
}

static inline void vnorm(void *out, void *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(v) : "memory");
}

static inline void vcross(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void xform(void *out, void *m, void *v)
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
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}

static inline float vdot(void *a, void *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2", "memory");
    return d;
}

static inline float fsqrt(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

float func_00045A20(char *o, char *w, Vec4 *tgt, float r, float spd)
{
    Vec4 dn;
    Vec4 z;
    Vec4 y;
    Vec4 x;
    Vec4 c;
    Vec4 p1;
    Vec4 d;
    Vec4 p2;
    float cam[16] __attribute__((aligned(16)));
    float inv[16] __attribute__((aligned(16)));
    Vec4 pos;
    Vec4 u;
    char *base;
    float len;
    float a;
    float t;
    int n;

    memset(&pos, 0, 16);
    pos.f[3] = 1.0f;
    base = o + 0x320;
    vsub3(&d, tgt, base);
    d.f[3] = 1.0f;
    len = vlen(&d);
    vscale4(&dn, &d, 1.0f / len);
    vnorm(&z, o + 0x330);
    vcross(&y, &z, &dn);
    vnorm(&y, &y);
    vcross(&x, &y, &z);
    x.f[3] = 0.0f;
    y.f[3] = 0.0f;
    z.f[3] = 0.0f;
    iosSetCameraMatrix(cam, &pos, &z, &y);
    matInverse(inv, cam);
    if (len < r + r)
        r = len * 0.5f;
    vscale4(&c, &x, r);
    vadd3(&c, base, &c);
    vsub3(&d, tgt, &c);
    xform(&d, cam, &d);
    d.f[1] = 0.0f;
    len = vlen(&d);
    if (AI_CalcIntersectionCircleXZ(&p1, &p2, &ZeroPoint, &d, r, fsqrt(len * len - r * r)) > 0) {
        xform(w + 0x60, inv, &p1);
        vadd3(w + 0x60, w + 0x60, &c);
        vsub3(w + 0x40, tgt, w + 0x60);
        vscale4(w + 0x40, w + 0x40, spd / vlen(w + 0x40));
    }
    vnorm(&u, &p1);
    a = iosGetACosfExact(vdot(&XUnitVectorInv, &u));
    if (u.f[2] < 0.0f)
        a = 6.2831852f - a;
    vscale4(w + 0x30, o + 0x330, F(o, 0x354) / F(o, 0x350));
    Q(w, 0x50) = *(s128 *)base;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(w + 0x70) : "memory");
    t = r * a / spd;
    F(w, 0xA0) = t;
    F(w, 0xA4) = gcGlobalVar.dt * F(o, 0x350);
    if (t < gcGlobalVar.dt * F(o, 0x350))
        F(w, 0xA0) = gcGlobalVar.dt * F(o, 0x350);
    {
    register char *p20 __asm__("$17") = w + 0x20;
    register char *p50 __asm__("$16");
    __asm__ __volatile__("" : : "r"(p20));
    p50 = w + 0x50;
    n = 0x20;
    AI_GetAccelC3XYZ(p20, w + 0x30, w + 0x40, p50, w + 0x60, w + 0x70, F(w, 0xA0));
    AI_GetAccelA3XYZ(w, w + 0x30, p50, w + 0x60, w + 0x70, w + n, F(w, 0xA0));
    AI_GetAccelB3XYZ(w + 0x10, w + 0x30, w + 0x40, p50, w + 0x60, p20, F(w, 0xA0));
    }
    return F(w, 0xA0);
}
#endif
