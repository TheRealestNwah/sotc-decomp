/* Parked: 23 diffs. Emitter visibility clip: sphere (shape type 1, clipBySphere) or oriented box
   (type 2: quaternion matrix times the camera matrix at 0x5A0, clipByMinMaxCube). The clobber-free
   translation asm stops gcc keeping &m in $s0 across iosgluGetCameraContext, and the register pins
   in quatMatrix give the Original's a0/a1/a2. Remaining: the box corner loads, negations and
   stores are scheduled differently (the Original loads 0x74, 0x4, 0x70 and stores hi.x/hi.y
   after the first corner copy). */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } __attribute__((aligned(8))) Vec;
typedef union { s128 q; float f[4]; } Vec4;

extern char *iosgluGetCameraContext(void);
extern int clipBySphere(void *sphere);
extern int clipByMinMaxCube(void *a, void *b, void *m);

static inline void scaleXYZ(Vec4 *out, void *a, float factor)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(factor) : "memory");
}

static inline void addXYZ(Vec4 *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void quatMatrix(void *dst0, void *q0, void *t0)
{
    register void *dst asm("$4") = dst0;
    register void *q asm("$6") = q0;
    register void *t asm("$5") = t0;
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
                         : : "r"(dst), "r"(q) : "memory");
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(dst), "r"(t));
}

static inline void mulMatrix(void *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "lqc2 vf24, 0x0(%2)\n"
                         "lqc2 vf25, 0x10(%2)\n"
                         "lqc2 vf26, 0x20(%2)\n"
                         "lqc2 vf27, 0x30(%2)\n"
                         "vmulax.xyzw ACC, vf14, vf24x\n"
                         "vmadday.xyzw ACC, vf15, vf24y\n"
                         "vmaddaz.xyzw ACC, vf16, vf24z\n"
                         "vmaddw.xyzw vf24, vf17, vf24w\n"
                         "vmulax.xyzw ACC, vf14, vf25x\n"
                         "vmadday.xyzw ACC, vf15, vf25y\n"
                         "vmaddaz.xyzw ACC, vf16, vf25z\n"
                         "vmaddw.xyzw vf25, vf17, vf25w\n"
                         "vmulax.xyzw ACC, vf14, vf26x\n"
                         "vmadday.xyzw ACC, vf15, vf26y\n"
                         "vmaddaz.xyzw ACC, vf16, vf26z\n"
                         "vmaddw.xyzw vf26, vf17, vf26w\n"
                         "vmulax.xyzw ACC, vf14, vf27x\n"
                         "vmadday.xyzw ACC, vf15, vf27y\n"
                         "vmaddaz.xyzw ACC, vf16, vf27z\n"
                         "vmaddw.xyzw vf27, vf17, vf27w\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf27, 0x30(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static int func_000BFF48(char *e, int *shape)
{
    Vec4 center;
    Vec4 tmp;
    Vec box[2];
    Vec hi;
    struct { Vec4 r[4]; } m;
    Vec4 m2[4];
    int ret = 0;

    scaleXYZ(&tmp, e + 0x30, *(float *)((char *)shape + 0x20));
    addXYZ(&center, e + 0x10, &tmp);
    if (shape[0] == 1) {
        center.f[3] = *(float *)&shape[1];
        if (clipBySphere(&center))
            ret = 1;
    } else if (shape[0] == 2) {
        float *s = (float *)shape;
        float z = s[0x1D];
        float y = s[0x1C];
        float x = s[1];
        box[1].x = -x * 0.5f;
        hi.x = x * 0.5f;
        box[1].y = -y * 0.5f;
        hi.y = y * 0.5f;
        box[1].z = -z * 0.5f;
        hi.z = z * 0.5f;
        box[1].w = 0.0f;
        hi.w = 0.0f;
        box[0] = box[1];
        box[1] = hi;
        quatMatrix(&m, e + 0x20, &center);
        m.r[3].f[3] = 1.0f;
        mulMatrix(m2, iosgluGetCameraContext() + 0x5A0, &m);
        ret = clipByMinMaxCube(&box[0], &box[1], m2) != 0;
    }
    return ret;
}
#endif
