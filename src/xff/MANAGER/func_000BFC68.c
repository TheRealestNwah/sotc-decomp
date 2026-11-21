typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern Vec4 YUnitVector, ZUnitVector;
extern void GetGeometryPointerPosition(void *, void *);
extern void GetGeometryPointerQuaternion(void *, void *);
extern void GetQuaternionByAxisDirZY(void *, Vec4 *, Vec4 *);
extern int func_000C5DF0(char *);

static inline void axisX(void *out, void *q)
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

static inline void axisY(void *out, void *q)
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

static inline void axisZ(void *out, void *q)
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

static inline void scaleXYZ(void *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v), "r"(s) : "memory");
}

static void func_000BFC68(char *e, char *a1, int a2)
{
    ((Vec4 *)(e + 0x40))->q = ((Vec4 *)(e + 0x10))->q;
    ((Vec4 *)(e + 0x50))->q = ((Vec4 *)(e + 0x20))->q;
    ((Vec4 *)(e + 0x60))->q = ((Vec4 *)(e + 0x30))->q;
    if (*(int *)(e + 0xC4) == 1) {
        GetGeometryPointerPosition(e + 0x10, e + 0xD0);
        if (func_000C5DF0(a1) == 1)
            GetQuaternionByAxisDirZY(e + 0x20, &YUnitVector, &ZUnitVector);
        else
            GetGeometryPointerQuaternion(e + 0x20, e + 0xD0);
        switch (*(unsigned *)(e + 0xC0)) {
        case 0:
            axisX(e + 0x30, e + 0x20);
            break;
        case 1:
            axisY(e + 0x30, e + 0x20);
            break;
        case 2:
            axisZ(e + 0x30, e + 0x20);
            break;
        case 3:
            axisX(e + 0x30, e + 0x20);
            scaleXYZ(e + 0x30, -1.0f);
            break;
        case 4:
            axisY(e + 0x30, e + 0x20);
            scaleXYZ(e + 0x30, -1.0f);
            break;
        case 5:
        default:
            axisZ(e + 0x30, e + 0x20);
            scaleXYZ(e + 0x30, -1.0f);
            break;
        }
    }
    if (a2 == 1) {
        ((Vec4 *)(e + 0x40))->q = ((Vec4 *)(e + 0x10))->q;
        ((Vec4 *)(e + 0x50))->q = ((Vec4 *)(e + 0x20))->q;
        ((Vec4 *)(e + 0x60))->q = ((Vec4 *)(e + 0x30))->q;
    }
}
