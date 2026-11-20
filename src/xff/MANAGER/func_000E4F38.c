typedef struct { float x, y, z, w; } __attribute__((aligned(8))) Vec4;
typedef float Mtx[4][4];

typedef struct {
    char pad0[0x10];
    float f10;
    float f14;
    float f18;
    float f1C;
    float f20;
    float f24;
    float f28;
    float f2C;
    float f30;
    char pad34[0x40 - 0x34];
    Mtx m40;
    Mtx m80;
    Mtx mC0;
    Mtx m100;
} VS;

extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern void iosUnitMatrix(Mtx);

static inline void mulMatrix(Mtx out, Mtx a, Mtx b)
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
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static void func_000E4F38(VS *vs)
{
    Vec4 half = { getDrawScreenWidth() >> 1, getDrawScreenHeight() >> 1, 0, 0 };
    Vec4 full = { 512.0f, 512.0f, 0, 0 };
    Mtx t;
    float tz, tw;
    float sx, sy;

    tw = (-vs->f28 * vs->f2C + vs->f24 * vs->f30) / (vs->f30 - vs->f2C);
    tz = vs->f30 * vs->f2C * (vs->f28 - vs->f24) / (vs->f30 - vs->f2C);
    iosUnitMatrix(vs->mC0);
    vs->mC0[0][0] = vs->f10;
    vs->mC0[2][2] = 0;
    vs->mC0[3][3] = 0;
    vs->mC0[3][2] = 1.0f;
    vs->mC0[2][3] = 1.0f;
    vs->mC0[1][1] = -vs->f10;
    iosUnitMatrix(t);
    t[0][0] = vs->f14;
    t[1][1] = vs->f18;
    t[3][0] = vs->f1C;
    t[3][1] = vs->f20;
    t[2][2] = tz;
    t[3][2] = tw;
    mulMatrix(vs->mC0, t, vs->mC0);

    sx = vs->f2C * half.x / vs->f10;
    sy = vs->f2C * half.y / vs->f10;
    iosUnitMatrix(vs->m40);
    vs->m40[0][0] = vs->f2C / sx;
    vs->m40[2][3] = 1.0f;
    vs->m40[1][1] = vs->f2C / sy;
    vs->m40[3][3] = 0;
    vs->m40[2][2] = (vs->f30 + vs->f2C) / (vs->f30 - vs->f2C);
    vs->m40[3][2] = vs->f30 * vs->f2C * -2.0f / (vs->f30 - vs->f2C);

    iosUnitMatrix(vs->m80);
    vs->m80[0][0] = vs->f10 * vs->f14 * sx / vs->f2C;
    vs->m80[3][3] = 1.0f;
    vs->m80[3][0] = vs->f1C;
    vs->m80[3][1] = vs->f20;
    vs->m80[2][2] = (vs->f24 - vs->f28) * 0.5f;
    vs->m80[3][2] = (vs->f28 + vs->f24) * 0.5f;
    vs->m80[1][1] = -vs->f10 * vs->f18 * sy / vs->f2C;

    sx = vs->f2C * full.x / vs->f10;
    sy = vs->f2C * full.y / vs->f10;
    iosUnitMatrix(vs->m100);
    vs->m100[0][0] = vs->f2C / sx;
    vs->m100[2][3] = 1.0f;
    vs->m100[1][1] = vs->f2C / sy;
    vs->m100[3][3] = 0;
    vs->m100[2][2] = (vs->f30 + vs->f2C) / (vs->f30 - vs->f2C);
    vs->m100[3][2] = vs->f30 * vs->f2C * -2.0f / (vs->f30 - vs->f2C);
}
