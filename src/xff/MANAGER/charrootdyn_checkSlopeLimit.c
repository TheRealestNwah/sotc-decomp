#ifdef NONMATCHING /* 66 diffs: address registers of the neg/matrix buffers swap (v0/v1); stack layout and VU0 text match */
typedef float Vec4[4] __attribute__((aligned(16)));

extern void *GetGeometryPointerSurfacePlane(void *);
extern float GetPointDistanceFromPlane(void *, void *);
extern float iosGetTableCos(int);

static inline void vecNegXYZ(float *out, float *v)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)
"
                         "vsubw.x vf5, vf0, vf0w
"
                         "vmulx.xyz vf11, vf11, vf5x
"
                         "sqc2 vf11, 0x0(%0)
"
                         : : "r"(out), "r"(v) : "memory");
}

static inline void quatToMatrix(float *out, float *quat)
{
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%1)\n"
                         "vmr32.w vf14, vf0\n"
                         "vmr32.w vf15, vf0\n"
                         "vmr32.w vf16, vf0\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf0, vf0\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf0, vf0\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "sqc2 vf14, 0x0(%0)\n"
                         "sqc2 vf15, 0x10(%0)\n"
                         "sqc2 vf16, 0x20(%0)\n"
                         : : "r"(out), "r"(quat));
}

static inline void matSetIdentityRow(float *row)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n"
                         : : "r"(row) : "memory");
}

static inline void matApply(float *out, float *m, float *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}


int charrootdyn_checkSlopeLimit(void *chr, float *vec, void *pos, int *cb)
{
    Vec4 m[4];
    Vec4 neg;
    Vec4 res;
    int type = cb[0];
    void *plane;
    int (*fn)(void *);

    vecNegXYZ(neg, vec);
    quatToMatrix(m[0], neg);
    matSetIdentityRow(m[3]);
    plane = GetGeometryPointerSurfacePlane(chr);
    matApply(res, m[0], (float *)plane);
    if (res[1] < iosGetTableCos(0x2AAA)) {
        if (type == 2) {
            return 0;
        }
        fn = (int (*)(void *))cb[2];
        if (fn == 0 || fn(chr) != 0) {
            if (type == 1 && GetPointDistanceFromPlane(plane, pos) > 0.0f) {
                return 0;
            }
            return 1;
        }
        return 0;
    }
    return 1;
}
#endif
