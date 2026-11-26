extern void gStatUnloadHorseChara(void);
extern void GetGeometryPointerPosition(float *, void *);
extern void clothmath_doubleTensionMove(float *, float *, float *, float, float, float);

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

typedef struct {
    float mat[16];
    float inv[16];
    float lim;
    float ofs;
    int sign;
} BridleParam;

static inline void mulMat4(float *dst, float *vec, float *mat)
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

static inline float len2xz(float *v)
{
    float d;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(v) : "$2");
    return d;
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

static inline void scaleXZ(float *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "mfc1 $8, %1\n"
                         "qmtc2.ni $8, vf6\n"
                         "vmulx.xz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v), "f"(s) : "$8", "memory");
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

static void func_0005D2C8(void)
{
    gStatUnloadHorseChara();
}

#ifdef NONMATCHING /* 6 diffs: prologue computes bp->inv from $s4 instead of the incoming $a2, and reloads cloth into $v0 instead of $v1 */
/* Cloth callback for the horse bridle strips: keeps each point beside the bridle frame (x limited by side, then a
   0.38-radius cylinder around the offset y/z and the xy plane), relaxes the strip toward the two geometry anchor
   points with clothmath_doubleTensionMove, and holds the last segment's length. */
static void func_0005D2E0(ClothObj *cloth, char *lay, BridleParam *bp)
{
    float tmp[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    int i;
    float *inv = bp->inv;
    float *tp;

    for (i = 0; i < 1; i++) {
        ClothDesc *desc = cloth->desc;
        char *row = cloth->rowTab;
        float *params = desc->params;
        int cols = desc->cols;
        float f20 = params[1];
        float f21 = params[2];
        float f22 = f20 * f20;
        float *p = *(float **)(row + 0x10) + 4;
        int j = cols - 3;
        int c;
        float lim = bp->lim;
        float ofs = bp->ofs;
        int n;
        int k;
        char *geo;
        int m;
        float *q;

        int last = cols - 1;
        int isign = bp->sign;

        if (j != -1) {
            tp = tmp;

            do {
                float off;
                float d;

                mulMat4(tp, p, inv);
                if (tmp[0] * (float)isign < lim * (float)isign)
                    tmp[0] = lim;
                off = ofs + tp[1];
                tmp[2] = tmp[2] - off;
                d = len2xz(tmp);
                if (d < 0.1444f)
                    scaleXZ(tp, fsqrt(0.1444f / d));
                tmp[2] = tmp[2] + off;
                if (ofs < tmp[2]) {
                    if (0.0f < tmp[1]) {
                        tmp[0] = (float)isign * 0.38f;
                        mulMat4(p, tp, bp->mat);
                    } else {
                        d = len2xy(tmp);
                        if (d < 0.1444f)
                            scaleXY(tp, fsqrt(0.1444f / d));
                    }
                }
                mulMat4(p, tp, bp->mat);
                p += 4;
            } while (--j != -1);
        }
        geo = (char *)cloth + 0x30;
        k = *(unsigned char *)(geo + 0x41);
        n = last - k;
        GetGeometryPointerPosition(*(float **)(row + 0x10) + n * 4, geo);
        c = n - 2;
        m = n - 1;
        q = *(float **)(row + 0x10) + 4;
        if (c != -1) {
            do {
                clothmath_doubleTensionMove(q, q + 4, q - 4, f22, f20, f21);
                q += 4;
            } while (--c != -1);
        }
        q = *(float **)(row + 0x10) + m * 4;
        c = m - 1;
        if (c != -1) {
            do {
                clothmath_doubleTensionMove(q, q - 4, q + 4, f22, f20, f21);
                q -= 4;
            } while (--c != -1);
        }
        if (k != 0) {
            float *r;
            GetGeometryPointerPosition(*(float **)(row + 0x10) + last * 4, (char *)cloth + 0x30);
            r = *(float **)(row + 0x10) + desc->cols * 4 - k * 4;
            c = k - 1;
            if (c != -1) do {
                float *nx;
                if (c != 0) {
                    nx = r + 4;
                    clothmath_doubleTensionMove(r, nx, r - 4, f22, f20, f21);
                } else {
                    float qq;
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
                                         : "=r"(qi) : "r"(r), "r"(r - 4), "r"(delta) : "memory");
                    __asm__("mtc1 %1, %0" : "=f"(qq) : "r"(qi));
                    nx = r + 4;
                    if (qq < f21) {
                        float s = f20 * qq;
                        __asm__ __volatile__("lqc2 vf7, 0x0(%0)\n"
                                             "lqc2 vf5, 0x0(%1)\n"
                                             "mfc1 $8, %2\n"
                                             "qmtc2.ni $8, vf6\n"
                                             "vmulx.xyz vf5, vf5, vf6x\n"
                                             "vadd.xyz vf7, vf7, vf5\n"
                                             "sqc2 vf7, 0x0(%3)\n"
                                             : : "r"(r - 4), "r"(delta), "f"(s), "r"(r) : "$8", "memory");
                    }
                }
                r = nx;
            } while (--c != -1);
        }
    }
}
#endif
