#ifdef NONMATCHING
/* lerp reads q through the hoisted $sp copy and two addu operands swap; otherwise matches. */
typedef unsigned int qword __attribute__((mode(TI)));

typedef union {
    float v[4];
    qword q;
} Quat;

static inline float dot4(Quat *a, Quat *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x0(%2)\n"
                         "vmul.xyzw vf15, vf14, vf15\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "qmfc2.ni $2, vf15
" "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline void scale4(Quat *out, Quat *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline void lerp4(Quat *out, Quat *a, Quat *b, float t)
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

void GetBlendedMotion(Quat *out, Quat *a, Quat *b, int n, float t)
{
    int i;
    Quat q;
    union {
        float f;
        int i;
    } d;

    for (i = 0; i < n; i++) {
        Quat *po = &out[i];
        Quat *pa = &a[i];

        q.q = b[i].q;
        d.f = dot4(pa, &q);
        if (d.i < 0) {
            scale4(&q, &q, -1.0f);
        }
        lerp4(po, pa, &q, t);
    }
}
#endif
