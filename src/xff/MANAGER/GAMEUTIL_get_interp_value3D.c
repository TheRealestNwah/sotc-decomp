typedef int s128 __attribute__((mode(TI)));

typedef union Vector {
    s128 quad;
    float v[4];
} Vector;

void GAMEUTIL_get_interp_value3D(Vector *out, Vector *a, Vector *b, float t)
{
    if (t <= 0.0f) {
        out->quad = b->quad;
        return;
    }
    if (t >= 1.0f ||
        (a->v[0] == b->v[0] && a->v[1] == b->v[1] && a->v[2] == b->v[2])) {
        out->quad = a->quad;
        return;
    }
    __asm__ __volatile__(".set noreorder\n"
                         "mfc1 $8, %0\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyz ACC, vf5, vf7x\n"
                         "vmaddw.xyz vf5, vf6, vf8w\n"
                         "sqc2 vf5, 0x0(%3)\n"
                         ".set reorder\n"
                         : : "f"(t), "r"(a), "r"(b), "r"(out) : "memory", "$8");
}
