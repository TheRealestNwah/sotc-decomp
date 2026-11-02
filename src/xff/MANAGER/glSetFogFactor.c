typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct {
    char *matrices;
    char pad4[0x5C];
    unsigned int fog;
} GlState;

extern GlState D_00130480;
extern float getFogFactor0(void);
extern float getFogFactor1(void);

float glSetFogFactor(float *position)
{
    Vec4 factor;
    GlState *gl;
    float result;

    factor.f[0] = getFogFactor0();
    factor.f[3] = getFogFactor1();
    gl = &D_00130480;
    __asm__ __volatile__("lqc2 vf27, 0x0(%1)\n"
                         "lqc2 vf28, 0x10(%1)\n"
                         "lqc2 vf29, 0x20(%1)\n"
                         "lqc2 vf30, 0x30(%1)\n"
                         "lqc2 vf23, 0x0(%2)\n"
                         "lqc2 vf24, 0x0(%3)\n"
                         "li.s $f1, 255.0\n"
                         "mfc1 $8, $f1\n"
                         "qmtc2.ni $8, vf26\n"
                         "vmulax.xyzw ACC, vf27, vf23x\n"
                         "vmadday.xyzw ACC, vf28, vf23y\n"
                         "vmaddaz.xyzw ACC, vf29, vf23z\n"
                         "vmaddw.xyzw vf23, vf30, vf23w\n"
                         "vmr32.w vf25, vf24\n"
                         "vmax.w vf23, vf23, vf0\n"
                         "vdiv Q, vf0w, vf23w\n"
                         "vwaitq\n"
                         "vmula.w ACC, vf24, vf0\n"
                         "vmaddq.w vf31, vf25, Q\n"
                         "vaddw.x vf31, vf0, vf31w\n"
                         "vmini.x vf31, vf31, vf26\n"
                         "vmax.x vf31, vf31, vf0\n"
                         "qmfc2.ni $8, vf31\n"
                         "mtc1 $8, %0\n"
                         : "=f"(result)
                         : "r"(gl->matrices + 0x660), "r"(position), "r"(&factor)
                         : "$8", "$f1", "memory");
    gl->fog = result;
    return result;
}
