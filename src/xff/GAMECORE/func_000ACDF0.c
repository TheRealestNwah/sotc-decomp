typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef union {
    u_long128 q;
    Vec4 f;
} VecQ;

typedef struct {
    int t[45];
} Tbl;

extern void *memset(void *, int, unsigned int);
extern float iosGetRandom(void);

static inline void vecAddXYZ(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float vecDist(float *a, float *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static void func_000ACDF0(char *pt, float *area, char *kite)
{
    VecQ off;
    VecQ save;
    Vec4 a;
    Vec4 b;
    union {
        Tbl s;
        struct {
            Vec4 np;
            VecQ o;
        } c;
    } u;
    float step = area[4] * 0.70710677f * 2.0f / 3.0f;
    int prev = *(int *)(kite + 0x1E4);
    int sel;

    save.q = *(u_long128 *)pt;
    memset(a, 0, 0x10);
    a[3] = 1.0f;
    memset(b, 0, 0x10);
    b[3] = 1.0f;
    u.s = (Tbl){{2, 2, 2, 2, 7, 3, 3, 3, 3, 6, 8, 8, 8, 8, 3, 7, 7, 7, 7, 8, 1, 3, 5,
                 7, 7, 1, 1, 1, 1, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 2, 6, 6, 6, 6, 1}};
    sel = u.s.t[prev * 5 + (int)(iosGetRandom() * 4.99)];
    a[0] = iosGetRandom() * step * 0.5f;
    a[2] = iosGetRandom() * step * 0.5f;
    if (sel % 3 == 0)
        b[0] = -step * 1.5f;
    else if ((sel - 1) % 3 == 0)
        b[0] = -step * 0.5f;
    else
        b[0] = step * 0.5f;
    if (sel < 3)
        b[2] = -step * 1.5f;
    else if (sel < 6)
        b[2] = -step * 0.5f;
    else
        b[2] = step * 0.5f;
    vecAddXYZ(off.f, a, b);
    *(int *)(kite + 0x1E4) = sel;
    off.f[1] = (iosGetRandom() - 0.5f) * area[5] * 2.0f;
    {
        float dy;
        float d;

        vecAddXYZ(u.c.np, area, off.f);
        u.c.o.q = save.q;
        dy = u.c.o.f[1] - u.c.np[1];
        if (dy < 0.0f)
            dy = -dy;
        u.c.np[1] = 0.0f;
        u.c.o.f[1] = 0.0f;
        d = vecDist(u.c.o.f, u.c.np);
        if (d < dy) {
            if (off.f[1] < 0.0f)
                d = -d;
            off.f[1] = d;
        }
    }
    vecAddXYZ((float *)pt, area, off.f);
    if (++*(int *)(pt + 0x10) > 0xFFFFFF)
        *(int *)(pt + 0x10) = 100;
    *(int *)(pt + 0x14) = *(int *)(kite + 0x1BC + (int)((iosGetRandom() - 0.0001f) * 10.0f) * 4);
}
