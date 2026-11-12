typedef struct {
    int unk0;
    int rows;
    int cols;
    char pad0C[0x1C];
    float *params;
} ClothDesc;

typedef struct {
    ClothDesc *desc;
    int unk4;
    int unk8;
    char *rowTab;
} ClothObj;

static inline void mulMat4(float *dst, float *vec, char *mat)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%1)\n"
                         "lqc2 vf14, 0x0(%2)\n"
                         "lqc2 vf15, 0x10(%2)\n"
                         "lqc2 vf16, 0x20(%2)\n"
                         "lqc2 vf17, 0x30(%2)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(dst), "r"(vec), "r"(mat) : "memory");
}

#ifdef NONMATCHING /* 106 diffs, same word count: draft with VU0 asm blocks; loop-count constants and a-register assignment differ */
static void func_0005E108(ClothObj *cloth, int unused, char *world)
{
    ClothDesc *desc = cloth->desc;
    float tmp[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float f3 = desc->params[1];
    float f4 = desc->params[2];
    char *row = *(char **)&cloth->rowTab;
    int r, c, k;

    r = desc->rows - 1;
    if (r != -1) do {
        float *prev = *(float **)(row + 0x10);
        c = desc->cols - 2;
        if (c != -1) do {
            float *p = prev + 4;
            char *col = world;

            k = *(int *)(world + 0x120) - 1;
            if (k != -1) do {
                mulMat4(tmp, p, col + 0x40);
                if (*(float *)(col + 0x84) < tmp[2] && tmp[2] < 0.0f) {
                    float d;
                    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                                         "vmul.xy vf7, vf7, vf7\n"
                                         "vaddy.x vf7, vf7, vf7y\n"
                                         "qmfc2.ni $2, vf7\n"
                                         "mtc1 $2, %0\n"
                                         : "=f"(d) : "r"(tmp) : "$2");
                    if (d < *(float *)(col + 0x80)) {
                        float s = *(float *)(col + 0x80) / d;
                        __asm__("sqrt.s %0, %1" : "=f"(s) : "f"(s));
                        {
                            int si;
                            __asm__ __volatile__("mfc1 %0, %1" : "=r"(si) : "f"(s));
                            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                                 "qmtc2.ni %1, vf6\n"
                                                 "vmulx.xy vf5, vf5, vf6x\n"
                                                 "sqc2 vf5, 0x0(%0)\n"
                                                 : : "r"(tmp), "r"(si) : "memory");
                        }
                        mulMat4(p, tmp, col);
                    }
                }
            } while (k--, col += 0x90, k != -1);
            {
                float q;
                int qi;
                __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                     "lqc2 vf6, 0x0(%2)\n"
                                     "vsub.xyzw vf8, vf5, vf6\n"
                                     "vmul.xyz vf7, vf8, vf8\n"
                                     "vaddy.x vf7, vf7, vf7y\n"
                                     "vaddz.x vf7, vf7, vf7z\n"
                                     "vrsqrt Q, vf0w, vf7x\n"
                                     "sqc2 vf8, 0x0(%3)\n"
                                     "vwaitq\n"
                                     "cfc2.ni %0, $vi22\n"
                                     : "=r"(qi) : "r"(p), "r"(prev), "r"(delta) : "memory");
                __asm__("mtc1 %1, %0" : "=f"(q) : "r"(qi));
                if (q < f4) {
                    int si;
                    float s = f3 * q;
                    __asm__ __volatile__("mfc1 %0, %1" : "=r"(si) : "f"(s));
                    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                                         "lqc2 vf5, 0x0(%2)\n"
                                         "qmtc2.ni %3, vf6\n"
                                         "vmulx.xyz vf5, vf5, vf6x\n"
                                         "vadd.xyz vf7, vf7, vf5\n"
                                         "sqc2 vf7, 0x0(%0)\n"
                                         : : "r"(p), "r"(prev), "r"(delta), "r"(si) : "memory");
                }
            }
            prev = p;
        } while (--c != -1);
        row += 0x18;
    } while (--r != -1);
}
#endif
