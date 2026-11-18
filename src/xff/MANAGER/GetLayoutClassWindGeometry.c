typedef int s128 __attribute__((mode(TI)));

typedef union Vec {
    float v[4];
    s128 q;
} Vec;

typedef struct LayoutWind {
    char pad0[0x60];
    Vec dir;
    Vec wind;
    Vec len;
} LayoutWind;

typedef struct LayoutClass {
    char pad0[0x30];
    float vel[4] __attribute__((aligned(16)));
    char pad40[0x134 - 0x40];
    void *windArea;
    char pad138[0x19C - 0x138];
    LayoutWind *wind;
} LayoutClass;

extern float *GetWindVector(float *len, void *arg);

static inline void vscale3(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}

static inline void vadd3(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline float vlen3(void *p)
{
    float result;
    __asm__ __volatile__(
        "lqc2 vf7, 0(%1)
" "vmul.xyz vf7, vf7, vf7
"
        "vmulax.w ACC, vf0, vf7x
" "vmadday.w ACC, vf0, vf7y
"
        "vmaddz.w vf7, vf0, vf7z
" "vsqrt Q, vf7w
" "vwaitq
"
        "cfc2 $2, $vi22
" "mtc1 $2, %0
"
        : "=f"(result) : "r"(p) : "$2");
    return result;
}

void GetLayoutClassWindGeometry(LayoutClass *obj, float *vel)
{
    float tmp[4] __attribute__((aligned(16)));
    float neg[4] __attribute__((aligned(16)));
    float rel[4] __attribute__((aligned(16)));
    float len;
    float *wind;

    wind = GetWindVector(&len, obj->windArea);
    if (vel != 0) {
        vscale3(tmp, vel, -1.0f);
        vadd3(obj->wind->dir.v, tmp, wind);
        obj->wind->len.v[0] = vlen3(obj->wind->dir.v);
    } else {
        obj->wind->dir.q = *(s128 *)wind;
        obj->wind->len.v[0] = len;
    }
    vscale3(neg, obj->vel, -1.0f);
    vadd3(rel, wind, neg);
    obj->wind->len.v[1] = vlen3(rel);
    obj->wind->wind.q = *(s128 *)wind;
}
