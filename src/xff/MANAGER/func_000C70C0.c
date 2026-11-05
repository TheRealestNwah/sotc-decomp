typedef struct { float f[16]; } F16;
typedef struct { float f[16]; } __attribute__((aligned(8))) F16A;

extern void *memset(void *, int, unsigned int);
extern void iosRotMatrixAxis(float *, float, float *, int);
extern void glBegin(int);
extern void glEnd(void);
extern void glColor4fv(float *);
extern void glTexCoord2fv(float *);
extern void glVertex4fv(float *);
extern F16 RO_0011A9A0;

static void func_000C70C0(char *d, float *uv, float *m2)
{
    F16 verts;
    F16A tc;
    F16A tmp;
    float mat[16] __attribute__((aligned(16)));
    int i;

    verts = RO_0011A9A0;
    memset(&tmp, 0, 0x40);
    tmp.f[4] = uv[0];
    tmp.f[12] = uv[0];
    tmp.f[9] = uv[1];
    tmp.f[13] = uv[1];
    tc = tmp;
    iosRotMatrixAxis(mat, *(float *)(d + 0x40), (float *)(d + 0x30), 1);
    __asm__ __volatile__(
        "mfc1 $8, %0\n"
        "lqc2 vf14, 0x0(%1)\n"
        "lqc2 vf15, 0x10(%1)\n"
        "lqc2 vf16, 0x20(%1)\n"
        "qmtc2.ni $8, vf10\n"
        "lqc2 vf17, 0x30(%1)\n"
        "vmr32.xyzw vf26, vf0\n"
        "vmr32.xyzw vf25, vf26\n"
        "vmr32.xyzw vf24, vf25\n"
        "vmulx.y vf25, vf25, vf10x\n"
        "vmul.x vf24, vf24, vf10\n"
        "vmulax.xyzw ACC, vf14, vf26x\n"
        "vmadday.xyzw ACC, vf15, vf26y\n"
        "vmaddaz.xyzw ACC, vf16, vf26z\n"
        "vmaddw.xyzw vf26, vf17, vf26w\n"
        "vmulax.xyzw ACC, vf14, vf25x\n"
        "vmadday.xyzw ACC, vf15, vf25y\n"
        "vmaddaz.xyzw ACC, vf16, vf25z\n"
        "vmaddw.xyzw vf25, vf17, vf25w\n"
        "vmulax.xyzw ACC, vf14, vf24x\n"
        "vmadday.xyzw ACC, vf15, vf24y\n"
        "vmaddaz.xyzw ACC, vf16, vf24z\n"
        "vmaddw.xyzw vf24, vf17, vf24w\n"
        "lqc2 vf14, 0x0(%2)\n"
        "lqc2 vf15, 0x10(%2)\n"
        "lqc2 vf16, 0x20(%2)\n"
        "lqc2 vf17, 0x30(%2)\n"
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
        "lqc2 vf27, 0x0(%3)\n"
        "lqc2 vf20, 0x0(%4)\n"
        "lqc2 vf21, 0x10(%4)\n"
        "lqc2 vf22, 0x20(%4)\n"
        "vmove.w vf27, vf0\n"
        "lqc2 vf23, 0x30(%4)\n"
        "vmulax.xyzw ACC, vf24, vf20x\n"
        "vmadday.xyzw ACC, vf25, vf20y\n"
        "vmaddaz.xyzw ACC, vf26, vf20z\n"
        "vmaddw.xyzw vf20, vf27, vf0w\n"
        "vmulax.xyzw ACC, vf24, vf21x\n"
        "vmadday.xyzw ACC, vf25, vf21y\n"
        "vmaddaz.xyzw ACC, vf26, vf21z\n"
        "vmaddw.xyzw vf21, vf27, vf0w\n"
        "vmulax.xyzw ACC, vf24, vf22x\n"
        "vmadday.xyzw ACC, vf25, vf22y\n"
        "vmaddaz.xyzw ACC, vf26, vf22z\n"
        "vmaddw.xyzw vf22, vf27, vf0w\n"
        "vmulax.xyzw ACC, vf24, vf23x\n"
        "vmadday.xyzw ACC, vf25, vf23y\n"
        "vmaddaz.xyzw ACC, vf26, vf23z\n"
        "vmaddw.xyzw vf23, vf27, vf0w\n"
        "sqc2 vf20, 0x0(%5)\n"
        "sqc2 vf21, 0x10(%5)\n"
        "sqc2 vf22, 0x20(%5)\n"
        "sqc2 vf23, 0x30(%5)\n"
        :
        : "f"(*(float *)(d + 0xC)), "r"(mat), "r"(m2), "r"(d), "r"(&verts), "r"(&tmp)
        : "memory", "$8");
    glBegin(5);
    glColor4fv((float *)(d + 0x10));
    for (i = 0; i < 4; i++) {
        glTexCoord2fv(&tc.f[i * 4]);
        glVertex4fv(&tmp.f[i * 4]);
    }
    glEnd();
}
