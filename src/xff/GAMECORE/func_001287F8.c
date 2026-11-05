typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef struct {
    float pos[4];
    float dir[4];
    float up[4];
} WormEnt;

typedef struct {
    WormEnt ent[32];
    float dist;
    int idx;
    int flag;
    char reset;
    char valid[32];
} WormHist;

typedef float Vec4[4] __attribute__((aligned(16)));

static inline void vecSub(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecAddXYZ(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vecNormalize(void *v)
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

static inline float vecDot(void *a, void *b)
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
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline void vecScale(void *dst, void *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

static void func_001287F8(WormHist *w)
{
    Vec4 a;
    Vec4 b;
    int i;

    for (i = 0; i < 32; i++) {
        int n = w->idx - i;
        int i1 = (n + 33) % 32;
        int i0 = (n + 32) % 32;
        int i2 = (n + 63) % 32;
        

        vecSub(a, w->ent[i0].pos, w->ent[i1].pos);
        vecSub(b, w->ent[i2].pos, w->ent[i0].pos);
        if (i == 0) {
            *(u_long128 *)a = *(u_long128 *)b;
        } else if (i == 31) {
            *(u_long128 *)b = *(u_long128 *)a;
        }
        vecAddXYZ(w->ent[i0].up, a, b);
        vecNormalize(w->ent[i0].up);
        vecNormalize(b);
        vecScale(w->ent[i0].up, w->ent[i0].up, 1.0f / vecDot(b, w->ent[i0].up));
    }
}
