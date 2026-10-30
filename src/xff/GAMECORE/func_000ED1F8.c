typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    int state;
    char pad4[0x50 - 4];
    Vec4 pos;
    int found;
    char pad64[0x70 - 0x64];
    Vec4 dir;
} Seeker;

extern int GAMEUTIL_is_yaw_pitch_get_direction(float *);

static inline float distXZSq(float *a, float *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline void vecSub(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
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

static void func_000ED1F8(Seeker *s, float *range, char *g)
{
    Vec4 pos;
    Vec4 dir;

    if (s->state != 1)
        return;
    pos.q = *(s128 *)(g + 0xB0);
    if (s->found) {
        float d = distXZSq(s->pos.f, pos.f);
        if (!(range[3] * range[3] <= d))
            return;
    }
    vecSub(dir.f, s->pos.f, pos.f);
    vecNormalize(dir.f, dir.f);
    if (GAMEUTIL_is_yaw_pitch_get_direction(dir.f) == 1) {
        s->found = 1;
        s->dir.q = dir.q;
        *(int *)(g + 0x18C8) = 1;
    }
}
