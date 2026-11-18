typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern int *GetGlDebugSw(void);
extern void iosScaleMatrixV(void *, void *, void *);
extern void glLoadMatrixf(void *);
extern void glEnable(int);
extern void glDisable(int);
extern void DebugDispBox(void *, int);
extern void func_0008CC60(void *, void *, void *, float *, float *);
extern void func_0008D058(float *, float, float, float);

static inline void quatMatrix(void *dst, void *q, void *t)
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
                         : : "r"(dst), "r"(q) : "memory");
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmove.w vf4, vf0\n"
                         "sqc2 vf4, 0x30(%0)\n"
                         : : "r"(dst), "r"(t) : "memory");
}

void DebugDispVolumeShapeColor(char *shape, float *color)
{
    Vec4 m[4];
    float size[2];

    if (*GetGlDebugSw() == 0)
        return;
    quatMatrix(m, shape + 0x10, shape);
    iosScaleMatrixV(m, m, shape + 0x40);
    glLoadMatrixf(m);
    glEnable(3);
    glEnable(7);
    glDisable(8);
    size[0] = *(float *)(shape + 0x58);
    size[1] = *(float *)(shape + 0x54);
    switch (*(int *)(shape + 0x50)) {
    case 0:
        func_0008CC60(shape, shape + 0x10, shape + 0x40, size, color);
        break;
    case 1:
        func_0008D058(color, size[1] * 0.5f, 1.0f, size[0]);
        break;
    case 2:
        DebugDispBox(m, 0);
        break;
    }
}
