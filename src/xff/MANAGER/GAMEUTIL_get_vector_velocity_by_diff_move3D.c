typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

static inline void scale(Vec4 *o, Vec4 *v, float s)
{
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "qmtc2 %2, vf06\n"
                         "vmulx.xyz vf05, vf05, vf06x\n"
                         "sqc2 vf05, 0(%0)\n"
                         ".set noreorder\n.set reorder\n"
                         : : "r"(o), "r"(v), "r"(s) : "memory");
}

static inline void sub(Vec4 *o, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "lqc2 vf06, 0(%2)\n"
                         "vsub.xyz vf05, vf05, vf06\n"
                         "sqc2 vf05, 0(%0)\n"
                         : : "r"(o), "r"(a), "r"(b) : "memory");
}

void GAMEUTIL_get_vector_velocity_by_diff_move3D(Vec4 *out, Vec4 *def, Vec4 *a, Vec4 *b, float t)
{
    if (t <= 0.0f) {
        out->q = def->q;
        return;
    }
    sub(out, b, a);
    scale(out, out, 1.0f / t);
}
