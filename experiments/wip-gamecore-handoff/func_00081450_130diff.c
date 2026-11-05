extern char *GetLayoutClass(void *);

#define MAT_APPLY(dst, mat, src) \
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n" \
                         "lqc2 vf14, 0x0(%1)\n" \
                         "lqc2 vf15, 0x10(%1)\n" \
                         "lqc2 vf16, 0x20(%1)\n" \
                         "lqc2 vf17, 0x30(%1)\n" \
                         "vmulax.xyzw ACC, vf14, vf8x\n" \
                         "vmadday.xyzw ACC, vf15, vf8y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf8z\n" \
                         "vmaddw.xyzw vf10, vf17, vf8w\n" \
                         "sqc2 vf10, 0x0(%0)\n" \
                         : : "r"(dst), "r"(mat), "r"(src) : "memory")

static inline float lenSqXY(float *v)
{
    float r;

    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xy vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(v) : "$2", "memory");
    return r;
}

static inline void scaleXY(float *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xy vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v), "r"(s) : "memory");
}

static int func_00081450(float *pos, void *obj)
{
    float t[4] __attribute__((aligned(16)));
    float u[4] __attribute__((aligned(16)));
    char *lay;
    int r = 0;
    int r2;
    float len;

    lay = GetLayoutClass(obj);
    MAT_APPLY(t, *(char **)(lay + 0x164) + 0x180, pos);
    if (t[2] < 0.0f && -0.07f < t[0]) {
        t[0] = -0.07f;
        MAT_APPLY(pos, *(char **)(lay + 0x158) + 0x180, t);
        r = 1;
    }
    MAT_APPLY(u, *(char **)(lay + 0x164) + 0x140, pos);
    if (u[2] < 0.0f) {
        len = lenSqXY(u);
        if (len < 0.0049f) {
            scaleXY(u, 0.07f / __builtin_sqrtf(len));
            MAT_APPLY(pos, *(char **)(lay + 0x158) + 0x140, u);
            r |= 1;
        }
    }
    r2 = 0;
    if (pos[1] < 9.01) {
        pos[1] = 9.01f;
        r2 = 1;
    }
    return r | r2;
}
