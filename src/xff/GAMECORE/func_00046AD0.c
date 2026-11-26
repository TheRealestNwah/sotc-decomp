/* Parked attempt, 24 diffs, same size (281 words incl. the split tail func_00046F10). Path-follow init (sibling of func_00046F48 / func_00047278): rotates RO_0017D1A0 (-0.02, 0.1, 0, 0) and ZUnitVectorInv by the layout's quaternion, adds the offset to the layout position, forces the direction's y to 1.0 and normalises it, scales w+0x90 and the direction into w+0x30 / w+0x40, gets the travel time from AI_GetTimeFromAccelC3 (projected speeds along the normalised chord), clamps it to 2pi / o+0x358 and dt * o+0x350, and calls AI_GetAccelC/A/B3XYZ. The inline getTime helper reproduces the early arg-register copies; rotate without the memory clobber rematerialises &off; a bare asm barrier before the lc+0x134 load puts the RO_0017D1A0 frame copy (ld 8 before ld 0) first. Remaining: the Original computes sp+0x20 before that copy, passes &off to vadd3 in a0, copies pos to w+0x60 from sp rather than through s1, and orders the ZeroVector store / 2*o+0x358 and the first AI call's t1 differently around the argument copies. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union {
    s128 q;
    float f[4];
} Vec4;
typedef union {
    float f[4];
    s128 q;
} Vec4F;
typedef struct { char pad[0x190]; float dt; } GcGlobal;

extern GcGlobal gcGlobalVar;
extern Vec4 ZUnitVectorInv;
extern Vec4 ZeroVector;
extern char *GetLayoutClass(int);
extern void AI_GetAccelA3XYZ(void *, void *, void *, void *, void *, void *, float);
extern void AI_GetAccelB3XYZ(void *, void *, void *, void *, void *, void *, float);
extern void AI_GetAccelC3XYZ(void *, void *, void *, void *, void *, void *, float);

#define F(p, o) (*(float *)((char *)(p) + (o)))

static inline void rotate(void *v, void *q)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
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
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(v), "r"(q) : "memory");
}

static inline void rotate_nm(void *v, void *q)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
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
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf0, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(v), "r"(q) );
}

static inline void vadd3(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void normalize(void *v)
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

static inline void vsub4(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
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

extern float AI_GetTimeFromAccelC3(float, float, float, float);

static inline void norm2(void *out, void *v)
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


static inline float getTime(void *p1, void *p0, void *v0, void *v1, float acc)
{
    Vec4 n1;
    Vec4 n2;
    Vec4 tmp;
    float len;
    float a;
    float b;

    vsub4(&tmp, p1, p0);
    len = vlen(&tmp);
    normalize(&tmp);
    norm2(&n1, v0);
    norm2(&n2, v1);
    a = vlen(v0) * vdot(&n1, &tmp);
    b = vlen(v1) * vdot(&n2, &tmp);
    return AI_GetTimeFromAccelC3(a, b, len, acc);
}

static void func_00046AD0(char *o, char *w)
{
    Vec4 pos;
    Vec4 dir;
    Vec4 *pd = &dir;
    Vec4 *pp = &pos;
    char *lc = GetLayoutClass(*(int *)(o + 8));
    Vec4F off = {{ -0.02f, 0.1f, 0.0f, 0.0f }};
    float t;
    char *w40;
    float lim;

    __asm__ __volatile__("");
    pp->q = **(s128 **)(lc + 0x134);
    rotate_nm(&off, *(void **)(lc + 0x13C));
    vadd3(pp, pp, &off);
    dir.q = ZUnitVectorInv.q;
    rotate(pd, *(void **)(lc + 0x13C));
    dir.f[1] = 1.0f;
    normalize(pd);
    vscale4(w + 0x30, w + 0x90, F(o, 0x354) / F(o, 0x350));
    vscale4(w + 0x40, &dir, F(o, 0x358));
    *(s128 *)(w + 0x60) = pp->q;
    *(s128 *)(w + 0x50) = *(s128 *)(w + 0x80);
    *(s128 *)(w + 0x70) = ZeroVector.q;
    w40 = w + 0x40;
    t = getTime(w + 0x60, w + 0x80, w + 0x30, w40, F(o, 0x358) + F(o, 0x358));
    F(w, 0xA0) = t;
    F(w, 0xA4) = gcGlobalVar.dt * F(o, 0x350);
    lim = 6.2831852f / F(o, 0x358);
    if (lim < t)
        F(w, 0xA0) = lim;
    if (F(w, 0xA0) < gcGlobalVar.dt * F(o, 0x350))
        F(w, 0xA0) = gcGlobalVar.dt * F(o, 0x350);
    AI_GetAccelC3XYZ(w + 0x20, w + 0x30, w40, w + 0x50, w + 0x60, w + 0x70, F(w, 0xA0));
    AI_GetAccelA3XYZ(w, w + 0x30, w + 0x50, w + 0x60, w + 0x70, w + 0x20, F(w, 0xA0));
    AI_GetAccelB3XYZ(w + 0x10, w + 0x30, w + 0x40, w + 0x50, w + 0x60, w + 0x20, F(w, 0xA0));
}
#endif
