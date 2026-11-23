/* Parked attempt, 5 diffs, same size. Per-state AI update: picks random timings, steers the velocity work areas with AI_UpdateVelocity, and in state 3 aims a random point around the target before calling func_00045A20. Inline wrappers on AI_GetRandomRange and AI_UpdateVelocity keep gcc from holding float constants across calls. Remaining: in cases 5-7 the Original computes the 3.1415926f product into $f20 (mul.s $f20,$f20,$f0) and divides from $f20; ours writes it to $f0. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern float AI_GetRandomRange(float, float);
extern int AI_UpdateVelocity(float *, float, float);
extern void iosGetDRandomVector(void *);
extern void func_000450B8(char *);
extern void func_00047570(char *);
extern int func_00047C78(char *);
extern void func_000479F0(char *, char *, float, float, float);
extern float func_00045A20(char *, char *, Vec4 *, float, float);
extern void func_000461E8(char *, char *);
extern void func_00046580(char *, char *);
extern void func_00046AD0(char *, char *);
extern void func_00047D88(char *);
extern void func_00044D08(char *, char *);

#define F(p, o) (*(float *)((char *)(p) + (o)))
#define Q(p, o) (*(s128 *)((char *)(p) + (o)))

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

static inline float RR(float a, float b)
{
    return AI_GetRandomRange(a, b);
}

static inline void UV(char *p, float a, float b)
{
    AI_UpdateVelocity((float *)p, a, b);
}

static void func_00048008(char *o)
{
    Vec4 p;
    Vec4 d;
    char *w;
    float A;
    float B;
    float C;
    float D;

    func_000450B8(o);
    func_00047570(o);
    switch (*(int *)(o + 0x38)) {
    case 1:
        B = RR(0.7f, 0.9f);
        UV(o + 0x350, 3.0f, 10.0f);
        if (F(o, 0x350) < 0.1f)
            F(o, 0x350) = 0.1f;
        func_00047C78(o);
        UV(o + 0x35C, 2.0f, 2.0f);
        A = F(o, 0x35C);
        UV(o + 0x360, B, 1.0f);
        B = F(o, 0x360);
        func_000479F0(o, o + 0x1B0, B, B * 3.1415926f / A, A);
        Q(o, 0x370) = Q(o, 0xD0);
        F(o, 0x374) = F(o, 0x184);
        break;
    case 2:
        B = RR(0.5f, 1.0f);
        UV(o + 0x35C, 2.5f, 3.0f);
        A = F(o, 0x35C);
        UV(o + 0x350, 3.0f, 10.0f);
        if (F(o, 0x350) < 0.1f)
            F(o, 0x350) = 0.1f;
        func_00047C78(o);
        func_000479F0(o, o + 0x1B0, B, B * 3.1415926f / A, A);
        Q(o, 0x370) = Q(o, 0xD0);
        F(o, 0x374) = F(o, 0x184);
        break;
    case 3:
        B = RR(1.3f, 1.3f);
        w = o + 0x100;
        C = F(o, 0x35C);
        if (F(w, 0xA4) > F(w, 0xA0)) {
            A = B * 6.0f;
            vsub3(&d, o + 0xE0, o + 0x320);
            if (vlen(&d) < A)
                iosGetDRandomVector(&p);
            else
                p.q = d.q;
            vscale4(&p, &p, A / vlen(&p));
            vadd3(&p, o + 0x320, &p);
            p.f[3] = 1.0f;
            func_00045A20(o, w, &p, B, C);
        }
        func_00047C78(o);
        Q(o, 0x370) = Q(o, 0xD0);
        F(o, 0x374) = F(o, 0x184);
        break;
    case 4:
        func_00047C78(o);
        Q(o, 0x370) = Q(o, 0xD0);
        F(o, 0x374) = F(o, 0x184);
        break;
    case 5:
        RR(0.8f, 1.0f);
        UV(o + 0x360, 1.0f, 3.0f);
        A = F(o, 0x360);
        UV(o + 0x35C, 15.0f, 50.0f);
        B = F(o, 0x35C);
        UV(o + 0x358, 25.0f, 3.0f);
        func_000461E8(o, o + 0x100);
        func_00047C78(o);
        D = A * 3.1415926f;
        func_000479F0(o, o + 0x1B0, A, D / B, B);
        Q(o, 0x370) = Q(o, 0x180);
        break;
    case 6:
        B = 20.0f;
        A = RR(0.3f, 0.6f);
        UV(o + 0x358, 25.0f, 10.0f);
        func_00046580(o, o + 0x100);
        func_00047C78(o);
        D = A * 3.1415926f;
        func_000479F0(o, o + 0x1B0, A, D / B, B);
        break;
    case 7:
        B = 20.0f;
        A = RR(0.3f, 0.6f);
        UV(o + 0x358, 25.0f, 10.0f);
        func_00046AD0(o, o + 0x100);
        func_00047C78(o);
        D = A * 3.1415926f;
        func_000479F0(o, o + 0x260, A, D / B, B);
        break;
    case 8:
        func_00047D88(o);
        break;
    }
    func_00044D08(o, o + 0x100);
}
#endif
