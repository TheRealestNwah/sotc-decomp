/* func_000461E8: Parked attempt, 9 diffs, same size.
 * The Original loads o->0x358 into $f20 before the first GetLayoutClass call;
 * ours schedules it into the call's delay slot.
 * AI_GetAccelC3XYZ's 6th argument ($t1) is set first in the Original, and the
 * B3 call reuses $s2 for w+0x40 where ours recomputes it.
 * new_var (from the permuter) breaks the w+0x40 CSE so $s2/$s3 match;
 * new_var2 and the do/while (0) block (also from the permuter) fix the
 * o+0xD0 and 0xA0 store order and the B3 call's $t1.
 * The (Vec4 *)->q store lets it alias the float loads that follow.
 */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union {
    s128 q;
    float f[4];
} Vec4;
typedef struct { char pad[0x190]; float dt; } GcGlobal;

extern GcGlobal gcGlobalVar;
extern char *GetLayoutClass(int);
extern void AI_GetAccelA3XYZ(void *, void *, void *, void *, void *, void *, float);
extern void AI_GetAccelB3XYZ(void *, void *, void *, void *, void *, void *, float);
extern void AI_GetAccelC3XYZ(void *, void *, void *, void *, void *, void *, float);

#define F(p, o) (*(float *)((char *)(p) + (o)))

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


static inline void lerp(void *out, void *a, void *b, float t)
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

static inline float vdist(void *a, void *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2", "memory");
    return d;
}

static void func_000461E8(char *o, char *w)
{
    Vec4 dir;
    int new_var;
    int new_var2;
    Vec4 t;
    Vec4 a;
    Vec4 b;
    float sp = F(o, 0x358);
    float len;
    float d;
    float f;
    float lo;
    s128 *pd;

    *(s128 *)(w + 0x50) = *(s128 *)(w + 0x80);
    ((Vec4 *)(w + 0x60))->q = **(s128 **)(GetLayoutClass(*(int *)(o + 8)) + 0x134);
    vscale4(w + 0x30, w + 0x90, F(o, 0x354) / F(o, 0x350));
    vsub4(&dir, w + 0x60, w + 0x50);
    normalize(&dir);
    lerp(w + 0x40, &dir, o + 0xF0, 0.7f);
    normalize(w + 0x40);
    vscale4(w + 0x40, w + 0x40, sp);
    len = vlen(o + 0x60);
    if (len > 0.0f)
        vscale4(&t, o + 0x60, 1.0f / len);
    d = vdot(&t, &dir);
    if (d > 0.0f)
        sp += len * d;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(w + 0x70) : "memory");
    d = vdist(w + 0x50, w + 0x60);
    lo = 150.0f;
    pd = (s128 *)(o + 0xD0);
    F(w, 0xA0) = d / sp;
    do {
        new_var = 0x40;
        a.q = **(s128 **)(GetLayoutClass(*(int *)(o + 8)) + 0x134);
        b.q = *pd;
        b.f[1] = 0.0f;
        a.f[1] = 0.0f;
        d = vdist(&a, &b);
        if (d <= lo)
            f = 1.0f;
        else if (d >= 200.0f)
            f = a.f[1];
        else
            f = 1.0f - (d - lo) / 50.0f;
        F(w, 0xA0) *= f;
        F(w, 0xA4) = gcGlobalVar.dt * F(o, 0x350);
        if (F(w, 0xA0) < gcGlobalVar.dt * F(o, 0x350))
            F(w, 0xA0) = gcGlobalVar.dt * F(o, 0x350);
        AI_GetAccelC3XYZ(w + 0x20, w + 0x30, w + new_var, w + 0x50, w + 0x60, w + 0x70, F(w, 0xA0));
        new_var2 = 0x20;
        AI_GetAccelA3XYZ(w, w + 0x30, w + 0x50, w + 0x60, w + 0x70, w + 0x20, F(w, 0xA0));
        AI_GetAccelB3XYZ(w + 0x10, w + 0x30, w + 0x40, w + 0x50, w + 0x60, w + new_var2, F(w, 0xA0));
    } while (0);
}
#endif
