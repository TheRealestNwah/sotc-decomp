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

static inline void collide(float *p, char *col, float *tmp)
{
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
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "mfc1 $8, %1\n"
                                 "qmtc2.ni $8, vf6\n"
                                 "vmulx.xy vf5, vf5, vf6x\n"
                                 "sqc2 vf5, 0x0(%0)\n"
                                 : : "r"(tmp), "f"(s) : "$8", "memory");
            mulMat4(p, tmp, col);
        }
    }
}

static void func_0005E848(ClothObj *cloth, int unused, char *world)
{
    ClothDesc *desc = cloth->desc;
    char *row = cloth->rowTab;
    register int r __asm__("$11") = desc->rows;
    float *params = desc->params;
    int cols = desc->cols;
    float f3 = params[1];
    float f4 = params[2];
    int c, k;
    float d1[4] __attribute__((aligned(16)));
    float d2[4] __attribute__((aligned(16)));

    while (r-- != 0) {
        register float *prev __asm__("$9") = *(float **)(row + 0x10);

        c = cols - 1;
        while (c-- != 0) {
            float *p = prev + 4;
            char *col;

            {
            float q;

            __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                 "lqc2 vf6, 0x0(%2)\n"
                                 "vsub.xyzw vf8, vf5, vf6\n"
                                 "vmul.xyz vf7, vf8, vf8\n"
                                 "vaddy.x vf7, vf7, vf7y\n"
                                 "vaddz.x vf7, vf7, vf7z\n"
                                 "vrsqrt Q, vf0w, vf7x\n"
                                 "sqc2 vf8, 0x0(%3)\n"
                                 "vwaitq\n"
                                 "cfc2.ni $2, $vi22\n"
                                 "mtc1 $2, %0\n"
                                 : "=f"(q) : "r"(p), "r"(prev), "r"(d1) : "$2", "memory");
            if (q < f4) {
                float s = f3 * q;

                __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                                     "lqc2 vf5, 0x0(%2)\n"
                                     "mfc1 $8, %3\n"
                                     "qmtc2.ni $8, vf6\n"
                                     "vmulx.xyz vf5, vf5, vf6x\n"
                                     "vadd.xyz vf7, vf7, vf5\n"
                                     "sqc2 vf7, 0x0(%0)\n"
                                     : : "r"(p), "r"(prev), "r"(d1), "f"(s) : "$8", "memory");
            }

            }
            k = *(int *)(world + 0x120);
            col = world;
            while (k-- != 0) {
                collide(p, col, d2);
                col += 0x90;
            }
            {

            float q;

            __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                 "lqc2 vf6, 0x0(%2)\n"
                                 "vsub.xyzw vf8, vf5, vf6\n"
                                 "vmul.xyz vf7, vf8, vf8\n"
                                 "vaddy.x vf7, vf7, vf7y\n"
                                 "vaddz.x vf7, vf7, vf7z\n"
                                 "vrsqrt Q, vf0w, vf7x\n"
                                 "sqc2 vf8, 0x0(%3)\n"
                                 "vwaitq\n"
                                 "cfc2.ni $2, $vi22\n"
                                 "mtc1 $2, %0\n"
                                 : "=f"(q) : "r"(p), "r"(prev), "r"(d2) : "$2", "memory");
            if (q < f4) {
                float s = f3 * q;

                __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                                     "lqc2 vf5, 0x0(%2)\n"
                                     "mfc1 $8, %3\n"
                                     "qmtc2.ni $8, vf6\n"
                                     "vmulx.xyz vf5, vf5, vf6x\n"
                                     "vadd.xyz vf7, vf7, vf5\n"
                                     "sqc2 vf7, 0x0(%0)\n"
                                     : : "r"(p), "r"(prev), "r"(d2), "f"(s) : "$8", "memory");
            }

            }
            prev = p;
        }
        row += 0x18;
    }
}

