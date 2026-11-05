extern char gcGlobalVar[];
extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, void *);
extern int AI_UpdateVelocity(float *, float, float);

#define VU_QUAT_MUL(dst, a, b)     __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"                          "lqc2 vf12, 0x0(%1)\n"                          "vmul.xyzw vf13, vf11, vf12\n"                          "vaddy.x vf13, vf13, vf13y\n"                          "vaddz.x vf13, vf13, vf13z\n"                          "vsubx.w vf13, vf13, vf13x\n"                          "vmulw.xyz vf14, vf12, vf11w\n"                          "vmulw.xyz vf15, vf11, vf12w\n"                          "vopmula.xyz ACC, vf12, vf11\n"                          "vopmsub.xyz vf16, vf11, vf12\n"                          "vadd.xyz vf13, vf14, vf15\n"                          "vadd.xyz vf13, vf13, vf16\n"                          "sqc2 vf13, 0x0(%2)\n"                          : : "r"(a), "r"(b), "r"(dst) : "memory")
extern char YUnitVector[];
extern float iosGetACosfExact(float);
extern int AI_GetSideSignalFromDirLev(void *, void *);
extern float AI_GetRotVelocity(float, float, float, float);

#define W(type, o) (*(type *)(ai + (o)))

static void func_0009CD78(char *ai, char *dir)
{
    float q[4] __attribute__((aligned(16)));
    char *layout;
    float a;
    float v;
    float scale;

    AI_UpdateVelocity((float *)(ai + 0x220), W(float, 0x210), *(float *)(W(char *, 0x20) + 0x10));
    AI_UpdateVelocity((float *)(ai + 0x224), W(float, 0x214), *(float *)(W(char *, 0x20) + 0x10));
    AI_UpdateVelocity((float *)(ai + 0x228), W(float, 0x218), *(float *)(W(char *, 0x20) + 0x10));
    scale = 32768.0f;
    a = iosGetACosfExact(*(float *)(dir + 0x50));
    v = AI_GetRotVelocity(W(float, 0x234) * 90.0f * 3.1415926f / 180.0f,
                          a * (float)AI_GetSideSignalFromDirLev(ai + 0x180, dir + 0x30), 3.0f, 0.099999997f);
    v *= 180.0f;
    v /= 282.74333f;
    W(float, 0x234) = v;
    v *= 90.0f;
    layout = GetLayoutClass(isysGetThisSubThread());
    v *= *(float *)(gcGlobalVar + 0x190);
    if (v < 0.0f ? v < -170.0f : 170.0f < v)
        v = v < 0.0f ? -170.0f : 170.0f;
    SetQuaternionByAxisRotateVWithNoRegularize(q, (int)(v * scale / 180.0f), YUnitVector);
    VU_QUAT_MUL(*(float **)(layout + 0x13C), q, *(float **)(layout + 0x13C));
}
