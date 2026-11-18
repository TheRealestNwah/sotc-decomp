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

static inline float len2xy(float *v)
{
    float d;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xy vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(v) : "$2");
    return d;
}

static inline void scaleXY(float *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "mfc1 $8, %1\n"
                         "qmtc2.ni $8, vf6\n"
                         "vmulx.xy vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v), "f"(s) : "$8", "memory");
}

static inline float fsqrt(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

static void T_0005DAB8(ClothObj *cloth, int unused, char *world)
{
    ClothDesc *desc = cloth->desc;
    float tmp[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    char *row = cloth->rowTab;
    int r = desc->rows;
    int cols = desc->cols;
    float *params = desc->params;
    float f3 = params[1];
    float f4 = params[2];
    int c;

    if (--r != -1) do {
        float *prev = *(float **)(row + 0x10);
        c = cols - 2;
        if (c != -1) do {
            float *p = prev + 4;
            float d;
            float lim;

            mulMat4(tmp, p, world + 0x40);
            if (tmp[2] < 0.0f) {
                d = len2xy(tmp);
                if (d < (lim = *(float *)(world + 0x180))) {
                    scaleXY(tmp, fsqrt(lim / d));
                    mulMat4(p, tmp, world);
                }
            } else {
                mulMat4(tmp, p, world + 0xC0);
                if (tmp[2] < 0.0f) {
                    d = len2xy(tmp);
                    if (d < (lim = *(float *)(world + 0x184))) {
                        scaleXY(tmp, fsqrt(lim / d));
                        mulMat4(p, tmp, world + 0x80);
                    }
                } else {
                    mulMat4(tmp, p, world + 0x140);
                    d = len2xy(tmp);
                    if (d < (lim = *(float *)(world + 0x188))) {
                        scaleXY(tmp, fsqrt(lim / d));
                        mulMat4(p, tmp, world + 0x100);
                    }
                }
            }
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
                    float s = f3 * q;
                    __asm__ __volatile__("lqc2 vf7, 0x0(%0)\n"
                                         "lqc2 vf5, 0x0(%1)\n"
                                         "mfc1 $8, %2\n"
                                         "qmtc2.ni $8, vf6\n"
                                         "vmulx.xyz vf5, vf5, vf6x\n"
                                         "vadd.xyz vf7, vf7, vf5\n"
                                         "sqc2 vf7, 0x0(%3)\n"
                                         : : "r"(prev), "r"(delta), "f"(s), "r"(p) : "$8", "memory");
                }
            }
            prev = p;
        } while (--c != -1);
        row += 0x18;
    } while (--r != -1);
}
