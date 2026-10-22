typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
/* dst = a * b */
#define VU_MUL_MATRIX(dst, a, b) \
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n" \
                         "lqc2 vf15, 0x10(%1)\n" \
                         "lqc2 vf16, 0x20(%1)\n" \
                         "lqc2 vf17, 0x30(%1)\n" \
                         "lqc2 vf24, 0x0(%2)\n" \
                         "lqc2 vf25, 0x10(%2)\n" \
                         "lqc2 vf26, 0x20(%2)\n" \
                         "lqc2 vf27, 0x30(%2)\n" \
                         "vmulax.xyzw ACC, vf14, vf24x\n" \
                         "vmadday.xyzw ACC, vf15, vf24y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf24z\n" \
                         "vmaddw.xyzw vf24, vf17, vf24w\n" \
                         "vmulax.xyzw ACC, vf14, vf25x\n" \
                         "vmadday.xyzw ACC, vf15, vf25y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf25z\n" \
                         "vmaddw.xyzw vf25, vf17, vf25w\n" \
                         "vmulax.xyzw ACC, vf14, vf26x\n" \
                         "vmadday.xyzw ACC, vf15, vf26y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf26z\n" \
                         "vmaddw.xyzw vf26, vf17, vf26w\n" \
                         "vmulax.xyzw ACC, vf14, vf27x\n" \
                         "vmadday.xyzw ACC, vf15, vf27y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf27z\n" \
                         "vmaddw.xyzw vf27, vf17, vf27w\n" \
                         "sqc2 vf24, 0x0(%0)\n" \
                         "sqc2 vf25, 0x10(%0)\n" \
                         "sqc2 vf26, 0x20(%0)\n" \
                         "sqc2 vf27, 0x30(%0)\n" \
                         : : "r"(dst), "r"(a), "r"(b) : "memory")
extern void *rootPtn;
extern void *iosgluCreateObject(void *);
extern void iosgluAddLineCylinderObject(void *, float, float, int, int, float);
extern void iosgluAddSphereObject(void *, float, int, int, int);
extern void iosUnitMatrix(float *);
extern void iosScaleMatrix(float *, float, float, float);
extern void iosRotMatrixX(float *, float);
extern void iosRotMatrixY(float *, float);
extern void glDrawGLUObj(void *, float *, void *, void *);
extern void glDrawBox(float *, float *, float *);

static void *D_0012FDF0 = 0;
static void *D_0012FDF4 = 0;

void DEBUG_disp_cylinder_object(float *pos, float *quat, void *color, void *mode, float axis, float radius, float height)
{
    Vec4 matrix[4];
    Vec4 offset[4];
    Vec4 scale[4];
    Vec4 rotation[4];
    Vec4 placement[4];
    float *out;
    if (D_0012FDF4 == 0) {
        D_0012FDF4 = iosgluCreateObject(&rootPtn);
        iosgluAddLineCylinderObject(D_0012FDF4, 1.0f, 1.0f, 10, 10, 2.0f);
    }
    iosUnitMatrix(offset[0].f);
    offset[3].f[2] = -1.0f;
    iosScaleMatrix(scale[0].f, radius, radius, height);
    if (axis <= 1.0f) {
        iosRotMatrixY(rotation[0].f, 1.5707963f);
    } else if (axis <= 2.0f) {
        iosRotMatrixX(rotation[0].f, 1.5707963f);
    } else if (axis <= 3.0f) {
        iosUnitMatrix(rotation[0].f);
    }
    out = placement[0].f;
    __asm__ __volatile__(".set noreorder\n"
        "vaddw.xyz vf12, vf0, vf0w\n"
        "lqc2 vf11, 0x0(%0)\n"
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
        "sqc2 vf14, 0x0(%1)\n"
        "sqc2 vf15, 0x10(%1)\n"
        "sqc2 vf16, 0x20(%1)\n"
        ".set reorder\n"
        : : "r"(quat), "r"(out));
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(out), "r"(pos) : "memory");
    VU_MUL_MATRIX(matrix, scale, offset);
    VU_MUL_MATRIX(matrix, rotation, matrix);
    VU_MUL_MATRIX(matrix, placement, matrix);
    glDrawGLUObj(D_0012FDF4, matrix[0].f, color, mode);
}

void DEBUG_disp_sphere_object(float *pos, float *quat, void *color, void *mode, float sx, float sy, float sz)
{
    Vec4 matrix[4];
    Vec4 scale[4];
    float *out;
    if (D_0012FDF0 == 0) {
        D_0012FDF0 = iosgluCreateObject(&rootPtn);
        iosgluAddSphereObject(D_0012FDF0, 1.0f, 10, 10, 0);
    }
    iosScaleMatrix(scale[0].f, sx, sy, sz);
    out = matrix[0].f;
    __asm__ __volatile__(".set noreorder\n"
        "vaddw.xyz vf12, vf0, vf0w\n"
        "lqc2 vf11, 0x0(%0)\n"
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
        "sqc2 vf14, 0x0(%1)\n"
        "sqc2 vf15, 0x10(%1)\n"
        "sqc2 vf16, 0x20(%1)\n"
        ".set reorder\n"
        : : "r"(quat), "r"(out));
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(out), "r"(pos) : "memory");
    VU_MUL_MATRIX(matrix, matrix, scale);
    glDrawGLUObj(D_0012FDF0, matrix[0].f, color, mode);
}

void DEBUG_disp_box_object(float *pos, float *quat, float *size, float *color)
{
    Vec4 matrix[4];
    float *out = matrix[0].f;
    __asm__ __volatile__(".set noreorder\n"
        "vaddw.xyz vf12, vf0, vf0w\n"
        "lqc2 vf11, 0x0(%0)\n"
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
        "sqc2 vf14, 0x0(%1)\n"
        "sqc2 vf15, 0x10(%1)\n"
        "sqc2 vf16, 0x20(%1)\n"
        ".set reorder\n"
        : : "r"(quat), "r"(out));
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(out), "r"(pos) : "memory");
    glDrawBox(matrix[0].f, size, color);
}
