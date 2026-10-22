typedef int Qword __attribute__((mode(TI)));

static inline void add(void *out, void *a, void *b)
{
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0(%1)\n"
                         "lqc2 vf6, 0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void normalize(void *out)
{
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(out) : "memory");
}

static inline void scale(void *out, void *a, float factor)
{
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(out), "r"(a), "r"(factor) : "memory");
}

static inline void cross(void *out, void *a, void *b)
{
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0(%1)\n"
                         "lqc2 vf6, 0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

void charrootdyn_getEdgeEffectivityCheckRayPosition(void *out0, void *out1,
                                                  void *out2, void *a, void *b,
                                                  void *position, void *normal,
                                                  float factor)
{
    Qword temporary[2];

    add(out0, a, b);
    normalize(out0);
    scale(out0, out0, factor);
    add(out0, position, out0);
    cross(out1, a, normal);
    scale(out1, out1, factor);
    scale(&temporary[0], a, factor);
    add(out1, out1, &temporary[0]);
    add(out1, position, out1);
    cross(out2, normal, b);
    scale(out2, out2, factor);
    scale(&temporary[1], b, factor);
    add(out2, out2, &temporary[1]);
    add(out2, position, out2);
}
