typedef float Vector[4] __attribute__((aligned(16)));

extern int DldSysUndefSymbol;
extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern void *iosgluGetCameraContext(void);
extern float GetScreenRadius(void *, void *, float);

static inline char *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;

    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != (char *)DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}

static inline void vecSub(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "lqc2 vf5, 0x0(%2)\n"
                         "vsub.xyzw vf6, vf4, vf5\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void directionZ(float *out, float *q)
{
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubx.z vf6, vf0, vf5x\n"
                         "vsuby.z vf6, vf6, vf5y\n"
                         "vaddw.y vf6, vf7, vf7w\n"
                         "vsuby.x vf6, vf8, vf8y\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.z vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(out), "r"(q) : "memory");
}

static inline float lengthSq(float *a)
{
    float r;
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)
"
                         "vmul.xyz vf5, vf4, vf4
"
                         "vaddy.x vf5, vf5, vf5y
"
                         "vaddz.x vf5, vf5, vf5z
"
                         "qmfc2.ni $2, vf5
"
                         "mtc1 $2, %0
"
                         : "=f"(r) : "r"(a) : "$2");
    return r;
}

/* The Original separates div.s and sqrt.s with three nops (shared FDIV unit). */
static inline float fsqrt(float x)
{
    float r;
    __asm__ __volatile__("nop\n"
                         "nop\n"
                         "nop\n"
                         "sqrt.s %0, %1"
                         : "=f"(r) : "f"(x));
    return r;
}

static inline float dot(float *a, float *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "lqc2 vf5, 0x0(%2)\n"
                         "vmul.xyz vf5, vf4, vf5\n"
                         "vaddy.x vf5, vf5, vf5y\n"
                         "vaddz.x vf5, vf5, vf5z\n"
                         "qmfc2.ni $2, vf5\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

#define CLIP_ACC(c) (*(float *)((c) + 0x1164))
#define CLIP_LAST(c) (*(float *)((c) + 0x1168))
#define CLIP_VAL(c) (*(float *)((c) + 0x116C))

float ViewIntervalClip(void *actor, void *target, float time)
{
    char *c = GetCharacterClass(actor);
    char *data;
    float limit;
    float acc;

    if (CLIP_VAL(c) == -1.0f) {
        acc = CLIP_ACC(c) + (time - CLIP_LAST(c));
        CLIP_LAST(c) = time;
        *(int *)(c + 0x1164) = 0;
        CLIP_VAL(c) = acc;
        return acc;
    }
    if (CLIP_LAST(c) < time) {
        limit = 0.0f;
        data = resourceData((unsigned int *)(*(char **)(c + 0x1140) + 0x12C));
        if (data != 0) {
            char *a = GetLayoutClass(actor);
            char *b = GetLayoutClass(target);
            Vector dir;
            Vector diff;
            float d;
            float proj;
            float r;

            vecSub(diff, *(float **)(a + 0x134), *(float **)(b + 0x134));
            directionZ(dir, *(float **)(b + 0x13C));
            d = dot(dir, diff);
            r = fsqrt(d / lengthSq(diff));
            if (d < 0.0f) {
                proj = -r;
            } else {
                proj = r;
            }
            r = GetScreenRadius(iosgluGetCameraContext(), *(float **)(a + 0x134), 1.0f);
            if (r <= *(float *)(data + 4) || proj < 0.0f) {
                limit = *(float *)(data + 0xC);
            } else if (*(float *)(data + 8) <= r) {
                limit = 0.0f;
            } else {
                limit = *(float *)(data + 0xC) * (*(float *)(data + 8) - r) / (*(float *)(data + 8) - *(float *)(data + 4));
            }
        }
        CLIP_ACC(c) += time - CLIP_LAST(c);
        CLIP_LAST(c) = time;
        acc = CLIP_ACC(c);
        if (limit <= acc) {
            CLIP_VAL(c) = acc;
            *(int *)(c + 0x1164) = 0;
        } else {
            *(int *)(c + 0x116C) = 0;
        }
    }
    return CLIP_VAL(c);
}
