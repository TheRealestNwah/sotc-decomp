#ifdef NONMATCHING /* 14 diffs: the axis pointers and the float scale temporaries take different registers */
typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef union { u_long128 q; float f[4]; } VecQ;

static inline void QuatAxisX(Vec4 *out, Vec4 *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubz.x vf6, vf7, vf7z\n"
                         "vaddx.y vf6, vf0, vf6x\n"
                         "vsuby.x vf6, vf0, vf5y\n"
                         "vsubz.x vf6, vf6, vf5z\n"
                         "vaddw.z vf6, vf8, vf8w\n"
                         "vsub.w vf6, vf6, vf6\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.x vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

static inline void QuatAxisY(Vec4 *out, Vec4 *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vaddy.z vf6, vf0, vf7y\n"
                         "vsubw.z vf6, vf6, vf7w\n"
                         "vsubx.y vf6, vf0, vf5x\n"
                         "vsubz.y vf6, vf6, vf5z\n"
                         "vaddz.x vf6, vf7, vf7z\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.y vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

static inline void QuatAxisZ(Vec4 *out, Vec4 *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubx.z vf6, vf0, vf5x\n"
                         "vsuby.z vf6, vf6, vf5y\n"
                         "vaddw.y vf6, vf7, vf7w\n"
                         "vsuby.x vf6, vf8, vf8y\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.z vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

static inline void VecScale(Vec4 *out, Vec4 *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(v), "r"(s) : "memory");
}

static inline void VecAdd(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

void GetOffsetPositionQuaternion(Vec4 *out, Vec4 *pos, Vec4 *offset, Vec4 *quat)
{
    Vec4 m[3];
    VecQ off;
    Vec4 tmp;

    QuatAxisX(&m[0], quat);
    QuatAxisY(&m[1], quat);
    QuatAxisZ(&m[2], quat);
    off.q = *(u_long128 *)offset;
    VecScale(&tmp, &m[0], off.f[0]);
    VecAdd(out, pos, &tmp);
    VecScale(&tmp, &m[1], off.f[1]);
    VecAdd(out, out, &tmp);
    VecScale(&tmp, &m[2], off.f[2]);
    VecAdd(out, out, &tmp);
}
#endif
