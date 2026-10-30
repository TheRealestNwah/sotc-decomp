extern char gcGlobalVar[];
extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern float AI_GetVelocity2(float, float, float, float);
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, void *);
extern int AI_UpdateVelocity(float *, float, float);

#define VU_QUAT_MUL(dst, a, b)     __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"                          "lqc2 vf12, 0x0(%1)\n"                          "vmul.xyzw vf13, vf11, vf12\n"                          "vaddy.x vf13, vf13, vf13y\n"                          "vaddz.x vf13, vf13, vf13z\n"                          "vsubx.w vf13, vf13, vf13x\n"                          "vmulw.xyz vf14, vf12, vf11w\n"                          "vmulw.xyz vf15, vf11, vf12w\n"                          "vopmula.xyz ACC, vf12, vf11\n"                          "vopmsub.xyz vf16, vf11, vf12\n"                          "vadd.xyz vf13, vf14, vf15\n"                          "vadd.xyz vf13, vf13, vf16\n"                          "sqc2 vf13, 0x0(%2)\n"                          : : "r"(a), "r"(b), "r"(dst) : "memory")

#define W(type, o) (*(type *)(ai + (o)))

static void func_0009CC50(char *ai)
{
    float q[4] __attribute__((aligned(16)));
    char *layout;
    float v;

    if (W(float, 0x1BC) <= W(float, 0x1B8)) {
        layout = GetLayoutClass(isysGetThisSubThread());
        v = AI_GetVelocity2(W(float, 0x264), W(float, 0x268), 0, W(float, 0x1BC));
        SetQuaternionByAxisRotateVWithNoRegularize(
            q, (int)(v * *(float *)(gcGlobalVar + 0x190) * 32768.0f / 3.1415926f), ai + 0x250);
        VU_QUAT_MUL(*(float **)(layout + 0x13C), q, *(float **)(layout + 0x13C));
    }
    AI_UpdateVelocity((float *)(ai + 0x220), W(float, 0x210), *(float *)(W(char *, 0x20) + 0x10));
    AI_UpdateVelocity((float *)(ai + 0x224), W(float, 0x214), *(float *)(W(char *, 0x20) + 0x10));
    AI_UpdateVelocity((float *)(ai + 0x228), W(float, 0x218), *(float *)(W(char *, 0x20) + 0x10));
    W(int, 0x234) = 0;
}
