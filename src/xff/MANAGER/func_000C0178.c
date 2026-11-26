typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef union { float f[4]; s128 q; } Col;
extern Vec4 All1Vector;

static void func_000C0178(char *obj, char *prm, char *a2, Vec4 *v, float *m0)
{
    register float *m __asm__("$12") = m0;
    Col c;
    int f;
    float *p;
    int i;

    if (*(int *)(obj + 0x110) != 0) {
        return;
    }
    {
    static const Col init = { { 1.0f, 1.0f, 1.0f, 1.0f } };
    c = init;
    }
    f = 0;
    switch (*(unsigned int *)(prm + 0x64)) {
    case 1:
        c.q = v[3].q;
        f = 1;
        break;
    case 2:
    case 3:
    case 4:
    case 5:
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vadd.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(c.f), "r"(&v[0]), "r"(&v[1]) : "memory");
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vadd.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(c.f), "r"(c.f), "r"(&v[2]) : "memory");
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "qmtc2.ni %2, vf6\n"
                             "vmulx.xyz vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(c.f), "r"(c.f), "r"(0.33333334f) : "memory");
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vadd.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(c.f), "r"(c.f), "r"(&v[3]) : "memory");
        f = 1;
        break;
    default:
        *(s128 *)(obj + 0x70) = All1Vector.q;
        break;
    }
    if (f == 1) {
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "qmtc2.ni %2, vf6\n"
                             "vmulx.xyz vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(c.f), "r"(c.f), "r"(*(float *)(prm + 0x6C)) : "memory");
        p = c.f;
        for (i = 0; i < 3; i++, p++) {
            if (*p < 0.0f) {
                *p = 0.0f;
            } else if (1.0f < *p) {
                *p = 1.0f;
            }
        }
        __asm__ __volatile__("mfc1 $8, %2\n"
                             "qmtc2.ni $8, vf7\n"
                             "lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%3)\n"
                             "vsubx.w vf8, vf0, vf7x\n"
                             "vmulax.xyz ACC, vf5, vf7x\n"
                             "vmaddw.xyz vf5, vf6, vf8w\n"
                             "sqc2 vf5, 0x0(%1)\n"
                             : : "r"(c.f), "r"(obj + 0x70), "f"(*(float *)(prm + 0x68)), "r"(&All1Vector) : "$8", "memory");
    }
    *(s128 *)(obj + 0x80) = v[3].q;
    if (*(int *)(prm + 0xB0) == 1 || *(int *)(a2 + 0x164) == 2) {
        *(float *)(obj + 0x90) = m[0];
        *(float *)(obj + 0x94) = m[4];
        *(float *)(obj + 0x98) = m[8];
        *(float *)(obj + 0x9C) = 0.0f;
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "qmtc2.ni %2, vf6\n"
                             "vmulx.xyz vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(obj + 0x90), "r"(obj + 0x90), "r"(-1.0f) : "memory");
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "vmul.xyz vf7, vf5, vf5\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             "vrsqrt Q, vf0w, vf7w\n"
                             "vwaitq\n"
                             "vmulq.xyz vf5, vf5, Q\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(obj + 0x90) : "memory");
    }
    *(int *)(obj + 0x110) = 1;
}
