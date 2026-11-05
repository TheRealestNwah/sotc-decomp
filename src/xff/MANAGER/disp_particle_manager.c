typedef struct {
    float m[16];
} Matrix;

extern Matrix D_001370F0;
extern void iosUnitMatrix(Matrix *m);
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern char *iosgluGetCameraContext(void);

void disp_particle_manager(void)
{
    Matrix *m = &D_001370F0;
    Matrix *cam;

    iosUnitMatrix(m);
    m->m[0] = 1.0f / (float)getDrawScreenWidth();
    m->m[5] = 1.0f / (float)getDrawScreenHeight();
    m->m[12] = -2048.0f / (float)getDrawScreenWidth() + 0.5f;
    m->m[13] = -2048.0f / (float)getDrawScreenHeight() + 0.5f;
    cam = (Matrix *)(iosgluGetCameraContext() + 0x660);
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf14, 0x0(%0)\n"
                         "lqc2 vf15, 0x10(%0)\n"
                         "lqc2 vf16, 0x20(%0)\n"
                         "lqc2 vf17, 0x30(%0)\n"
                         "lqc2 vf24, 0x0(%1)\n"
                         "lqc2 vf25, 0x10(%1)\n"
                         "lqc2 vf26, 0x20(%1)\n"
                         "lqc2 vf27, 0x30(%1)\n"
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
                         ".set reorder\n"
                         : : "r"(m), "r"(cam) : "memory");
}
