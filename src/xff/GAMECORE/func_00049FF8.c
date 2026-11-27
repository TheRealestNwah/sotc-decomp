extern int func_00049DA0(char *, float *, int);

/* The VU0 blocks are written at the call site so the pinned register
   variables reach the asm operands (an inline function's parameters
   would get fresh pseudos). */
#define VSUB4(d, a, b)                                  \
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"          \
                         "lqc2 vf6, 0x0(%2)\n"          \
                         "vsub.xyzw vf7, vf5, vf6\n"    \
                         "sqc2 vf7, 0x0(%0)\n"          \
                         : : "r"(d), "r"(a), "r"(b) : "memory")

#define VADD4(d, a, b)                                  \
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"          \
                         "lqc2 vf6, 0x0(%2)\n"          \
                         "vadd.xyzw vf7, vf5, vf6\n"    \
                         "sqc2 vf7, 0x0(%0)\n"          \
                         : : "r"(d), "r"(a), "r"(b) : "memory")

#define VADD3(d, b)                                     \
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"          \
                         "lqc2 vf6, 0x0(%1)\n"          \
                         "vadd.xyz vf5, vf5, vf6\n"     \
                         "sqc2 vf5, 0x0(%0)\n"          \
                         : : "r"(d), "r"(b) : "memory")

#define VNORMALIZE3(v)                                  \
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"          \
                         "vmul.xyz vf7, vf5, vf5\n"     \
                         "vmulax.w ACC, vf0, vf7x\n"    \
                         "vmadday.w ACC, vf0, vf7y\n"   \
                         "vmaddz.w vf7, vf0, vf7z\n"    \
                         "vrsqrt Q, vf0w, vf7w\n"       \
                         "vwaitq\n"                     \
                         "vmulq.xyz vf5, vf5, Q\n"      \
                         "sqc2 vf5, 0x0(%0)\n"          \
                         : : "r"(v) : "memory")

#define VSCALE4(v, si)                                  \
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"          \
                         "qmtc2.ni %1, vf6\n"           \
                         "vmulx.xyzw vf5, vf5, vf6x\n"  \
                         "sqc2 vf5, 0x0(%0)\n"          \
                         : : "r"(v), "r"(si) : "memory")

static inline void add4(float *d, float *a, float *b)
{
    VADD4(d, a, b);
}

static void func_00049FF8(char *p)
{
    float t[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    float q[4] __attribute__((aligned(16)));
    float s;
    float u[4] __attribute__((aligned(16)));
    int idx = func_00049DA0(p, u, *(int *)(p + 0x98));
    register char *base __asm__("$6");
    int i;

    *(int *)(p + 0x98) = idx;
    if (idx < *(int *)(p + 0x84) && idx > 0 && *(int *)(p + 0x8C)) {
        register float *pd __asm__("$2") = d;
        base = *(char **)(p + 0x70);
        {
            register float *cur __asm__("$3") = (float *)(base + idx * 16);
            register float *prv __asm__("$4") = cur - 4;
            VSUB4(pd, prv, cur);
        }
        VNORMALIZE3(pd);
        {
            register int si __asm__("$3");
            __asm__ __volatile__("mfc1 %0, %1" : "=r"(si) : "f"(u[0]));
            VSCALE4(pd, si);
        }
        {
            register float *pq __asm__("$5") = q;
            register float *cur __asm__("$3") = (float *)((*(int *)(p + 0x98) << 4) + (int)base);
            VADD4(pq, cur, pd);
            {
                register float *src __asm__("$4") = (float *)(p + 0xB0);
                VSUB4(t, src, pq);
            }
        }
        {
            register float *a __asm__("$2") = (float *)(p + 0x150);
            VADD3(a, t);
        }
        {
            register float *a __asm__("$3") = (float *)(p + 0x180);
            VADD3(a, t);
        }
        {
            register float *a __asm__("$2") = (float *)(p + 0x320);
            VADD3(a, t);
        }
        {
            float *c = (float *)base;
            i = 0;
            {
                register int n __asm__("$3") = *(int *)(p + 0x84);
                __asm__("" : "+r"(n));
                if (i >= n)
                    goto out;
            }
            do {
                add4(c, c, t);
                i++, c += 4;
            } while (i < *(int *)(p + 0x84));
        out:;
        }
    }
}
