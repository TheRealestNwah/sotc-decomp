typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0x104];
    float speed;
    char pad108[0x140 - 0x108];
    Vec4 pos;
} Body;

typedef struct {
    Body *body;
    char pad4[0x60 - 4];
    Vec4 vel;
    float time;
    float limit;
    int moving;
} Wander;

extern float iosGetRandom(void);
extern float AI_GetInterRatioOutCut(float, float, float, float, float);

static inline void vecClear(float *v)
{
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(v) : "memory");
}

static inline void vecNormalize(float *dst, float *src)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src) : "memory");
}

static inline void vecScale(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

static inline void vecAdd(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static void func_000523E8(Wander *w)
{
    float speed = w->body->speed;

    if (w->moving == 0) {
        if (w->limit > w->time) {
            float r = iosGetRandom();

            w->time = r * AI_GetInterRatioOutCut(speed, 0.0f, 1.0f, 1.0f, 0.1f);
            w->limit = 0.0f;
            vecClear(w->vel.f);
            w->vel.f[0] = iosGetRandom() * 2.0f - 1.0f;
            w->vel.f[2] = iosGetRandom() * 2.0f - 1.0f;
            vecNormalize(w->vel.f, w->vel.f);
            vecScale(w->vel.f, w->vel.f, speed);
            w->moving = 1;
        }
    } else if (w->limit > w->time) {
        w->time = 0.1f;
        w->limit = 0.0f;
        vecClear(w->vel.f);
        w->moving = 0;
    }
    vecAdd(w->body->pos.f, w->body->pos.f, w->vel.f);
}
