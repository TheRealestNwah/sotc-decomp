typedef int s128 __attribute__((mode(TI)));

typedef union {
    s128 q;
    float f[4];
} Vec4;

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

int chkUpPointForLineYZ(Vec4 *pt, Vec4 *a, Vec4 *b)
{
    Vec4 p;
    Vec4 s;
    Vec4 dir;
    Vec4 d;

    p.q = pt->q;
    s.q = a->q;
    dir.q = b->q;
    p.f[0] = 0.0f;
    s.f[0] = 0.0f;
    dir.f[0] = 0.0f;
    vecNormalize(&dir);
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(&d), "r"(&p), "r"(&s) : "memory");
    vecNormalize(&d);
    return 0.0f <= dir.f[1] * d.f[2] - dir.f[2] * d.f[1];
}
