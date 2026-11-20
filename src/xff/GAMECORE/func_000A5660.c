typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char *GetLayoutClass(int);
extern void *isysGetThisSubThread(void);
extern void AI_GetVelocity3XYZ(float *, float *, float *, float *, float *, float);
extern void AI_GetPosition3XYZ(float *, float *, float *, float *, float *, float *, float);
extern int AI_GetSideSignalFromDirLev(void *, void *);
extern float AI_GetRotVelocity(float, float, float, float);
extern void AI_UpdateVelocity(float *, float, float);
extern float iosGetACosfExact(float);
extern float iosGetASinfExact(float);
extern float AI_GetVelocity3(float, float, float, float, float);
extern float AI_GetPosition3(float, float, float, float, float, float);
extern s128 ZeroVector;

static inline void normalize3(float *v)
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

static inline void normalize3to(float *o, float *v)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "vmul.xyz vf7, vf5, vf5
"
                         "vmulax.w ACC, vf0, vf7x
"
                         "vmadday.w ACC, vf0, vf7y
"
                         "vmaddz.w vf7, vf0, vf7z
"
                         "vrsqrt Q, vf0w, vf7w
"
                         "vwaitq
"
                         "vmulq.xyz vf5, vf5, Q
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(o), "r"(v) : "$2", "memory");
}

#ifdef NONMATCHING /* 9 diffs: the 0.0 mtc1 into f21 is scheduled before the GetLayoutClass call instead of after the 0x290/0x740 loads (reorders, volatile/memory barriers and a 20 min permuter run did not move it). The $2 clobber on normalize3to puts the nv pointer in v1. */
static void func_000A5660(char *p)
{
    Vec4 vel, pos, dir, nv;
    float d, ang, side_f;
    float t, one, z2;
    register float zero __asm__("$f21");
    char *obj = GetLayoutClass((int)isysGetThisSubThread());

    t = *(float *)(p + 0x290);
    zero = 0.0f;
    z2 = zero;
    __asm__("" : "+f"(zero));
    one = 1.0f;
    *(float *)(p + 0x30C) = one;
    if (t <= *(float *)(p + 0x740)) {
        AI_GetVelocity3XYZ(vel.f, (float *)(p + 0x6B0), (float *)(p + 0x6C0), (float *)(p + 0x6D0), (float *)(p + 0x6E0), t);
        AI_GetPosition3XYZ(pos.f, (float *)(p + 0x6B0), (float *)(p + 0x6C0), (float *)(p + 0x6D0), (float *)(p + 0x700), (float *)(p + 0x6E0), t);
        AI_GetVelocity3(*(float *)(p + 0x748), *(float *)(p + 0x74C), *(float *)(p + 0x750), zero, t);
        pos.f[1] += AI_GetPosition3(*(float *)(p + 0x748), *(float *)(p + 0x74C), *(float *)(p + 0x750), z2, z2, t);
        pos.f[3] = one;
        (*(Vec4 **)(obj + 0x134))->q = pos.q;
        *(s128 *)(p + 0x730) = vel.q;
        dir.q = vel.q;
        dir.f[1] = zero;
        normalize3(dir.f);
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                             "lqc2 vf6, 0x0(%2)
"
                             "vaddw.x vf7, vf0, vf0w
"
                             "vmul.xyz vf6, vf5, vf6
"
                             "vaddax.x ACC, vf0, vf6x
"
                             "vmadday.x ACC, vf7, vf6y
"
                             "vmaddz.x vf6, vf7, vf6z
"
                             "qmfc2.ni %0, vf6
"
                             : "=r"(d) : "r"(dir.f), "r"(p + 0x240));
        ang = iosGetACosfExact(d);
        {
            int side = AI_GetSideSignalFromDirLev(p + 0x240, dir.f);
            *(float *)(p + 0x2F0) = d;
            side_f = (float)side;
            *(float *)(p + 0x2F4) =
                AI_GetRotVelocity(*(float *)(p + 0x2F4) * 90.0f * 3.1415927f / 180.0f, ang * side_f, 1.0f, 0.1f) * 180.0f / (90.0f * 3.1415927f);
        }
        *(float *)(p + 0x300) = zero;
        AI_UpdateVelocity((float *)(p + 0x2FC), zero, one);
        normalize3to(nv.f, vel.f);
        *(float *)(p + 0x304) = iosGetASinfExact(nv.f[1]);
    } else {
        AI_UpdateVelocity((float *)(p + 0x2F4), zero, one);
    }
    *(s128 *)(p + 0x2E0) = ZeroVector;
}
#endif
