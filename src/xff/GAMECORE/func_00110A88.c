typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0x6C];
    float height;
    float rot;
    char pad74[0x9C - 0x74];
    float scale;
} PathSpeed;

typedef struct {
    char pad0[0xC0];
    float range;
    char padC4[0xCC - 0xC4];
    PathSpeed *speed;
    char padD0[0xE0 - 0xD0];
    Vec4 step;
    char padF0[0x100 - 0xF0];
    Vec4 base;
    char pad110[0x158 - 0x110];
    float velY;
    float velZ;
} PathMove;

extern void iosRotMatrixY(float *, float);
extern s128 ZeroVector;
extern s128 ZUnitVector;
extern float chkTime2Int;

static inline void vecScale(float *out, float *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline void vecAdd(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void matApply(float *out, Vec4 *m, float *v)
{
    __asm__ __volatile__("lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0x0(%0)\n"
                         : : "r"(out), "r"(m), "r"(v) : "memory");
}

static inline void matMul(Vec4 *dst, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)
"
                         "lqc2 vf15, 0x10(%1)
"
                         "lqc2 vf16, 0x20(%1)
"
                         "lqc2 vf17, 0x30(%1)
"
                         "lqc2 vf24, 0x0(%2)
"
                         "lqc2 vf25, 0x10(%2)
"
                         "lqc2 vf26, 0x20(%2)
"
                         "lqc2 vf27, 0x30(%2)
"
                         "vmulax.xyzw ACC, vf14, vf24x
"
                         "vmadday.xyzw ACC, vf15, vf24y
"
                         "vmaddaz.xyzw ACC, vf16, vf24z
"
                         "vmaddw.xyzw vf24, vf17, vf24w
"
                         "vmulax.xyzw ACC, vf14, vf25x
"
                         "vmadday.xyzw ACC, vf15, vf25y
"
                         "vmaddaz.xyzw ACC, vf16, vf25z
"
                         "vmaddw.xyzw vf25, vf17, vf25w
"
                         "vmulax.xyzw ACC, vf14, vf26x
"
                         "vmadday.xyzw ACC, vf15, vf26y
"
                         "vmaddaz.xyzw ACC, vf16, vf26z
"
                         "vmaddw.xyzw vf26, vf17, vf26w
"
                         "vmulax.xyzw ACC, vf14, vf27x
"
                         "vmadday.xyzw ACC, vf15, vf27y
"
                         "vmaddaz.xyzw ACC, vf16, vf27z
"
                         "vmaddw.xyzw vf27, vf17, vf27w
"
                         "sqc2 vf24, 0x0(%0)
"
                         "sqc2 vf25, 0x10(%0)
"
                         "sqc2 vf26, 0x20(%0)
"
                         "sqc2 vf27, 0x30(%0)
"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline float vecLen(float *v)
{
    float len;
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)
"
                         "vmul.xyz vf7, vf7, vf7
"
                         "vmulax.w ACC, vf0, vf7x
"
                         "vmadday.w ACC, vf0, vf7y
"
                         "vmaddz.w vf7, vf0, vf7z
"
                         "vsqrt Q, vf7w
"
                         "vwaitq
"
                         "cfc2 $2, $vi22
"
                         "mtc1 $2, %0
"
                         : "=f"(len) : "r"(v) : "$2");
    return len;
}

static int func_00110A88(Vec4 *out, PathMove *p)
{
    Vec4 m[4];
    Vec4 step;
    Vec4 m2[4];
    Vec4 up;
    float t = 0.0f;
    PathSpeed *s = p->speed;
    float ry = s->rot;
    float rz = s->rot;
    float a = __builtin_fabsf(p->velY) / s->rot;
    float b = __builtin_fabsf(p->velZ) / s->rot;
    float dt = chkTime2Int;
    float n;

    if (2.0f < a + s->height || 2.0f < b + s->height) {
        out->q = p->base.q;
        return 0;
    }
    if (a < b) {
        n = b;
        ry *= a / n;
    } else {
        n = a;
        rz = b / n;
    }
    if (0.0f <= p->velY)
        iosRotMatrixY(m[0].f, -ry * dt);
    else
        iosRotMatrixY(m[0].f, ry * dt);
    if (0.0f <= p->velZ)
        iosRotMatrixY(m2[0].f, rz * dt);
    else
        iosRotMatrixY(m2[0].f, -rz * dt);
    matMul(m, m, m2);
    out->q = ZeroVector;
    step.q = p->step.q;
    vecScale(step.f, step.f, p->speed->scale);
    step.f[0] = -step.f[0];
    step.f[1] = -step.f[1];
    step.f[2] = -step.f[2];
    step.f[3] = 1.0f;
    vecScale(step.f, step.f, dt);
    while (t < n) {
        vecAdd(out->f, out->f, step.f);
        t += dt;
        matApply(step.f, m, step.f);
    }
    vecScale(up.f, (float *)&ZUnitVector, -p->speed->height);
    vecAdd(out->f, out->f, up.f);
    if (p->range < vecLen(out->f)) {
        out->q = p->base.q;
        return 0;
    }
    vecAdd(out->f, out->f, p->base.f);
    out->f[3] = 1.0f;
    return 1;
}
