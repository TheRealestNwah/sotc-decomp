typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0x64];
    float speed;
    char pad68[0xF0 - 0x68];
    float scale;
} PathSpeed;

typedef struct {
    char pad0[0xCC];
    PathSpeed *speed;
    char padD0[0xE0 - 0xD0];
    Vec4 step;
    char padF0[0x100 - 0xF0];
    Vec4 base;
    char pad110[0x138 - 0x110];
    float vel;
} PathMove;

extern void iosRotMatrixY(float *, float);
extern s128 ZeroVector;
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

static void func_0010A778(Vec4 *out, PathMove *p)
{
    Vec4 m[4];
    Vec4 step;
    float t = 0.0f;
    float vel = p->vel;
    PathSpeed *s = p->speed;
    float n = __builtin_fabsf(vel) / s->speed;
    float dt = chkTime2Int;

    if (0.0f <= vel)
        iosRotMatrixY(m[0].f, -s->speed * dt);
    else
        iosRotMatrixY(m[0].f, s->speed * dt);
    out->q = ZeroVector;
    step.q = p->step.q;
    vecScale(step.f, step.f, s->scale);
    step.f[0] = -step.f[0];
    step.f[2] = -step.f[2];
    step.f[3] = 1.0f;
    vecScale(step.f, step.f, dt);
    while (t < n) {
        vecAdd(out->f, out->f, step.f);
        t += dt;
        matApply(step.f, m, step.f);
    }
    vecAdd(out->f, out->f, p->base.f);
    out->f[3] = 1.0f;
}
