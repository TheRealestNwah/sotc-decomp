typedef int s128 __attribute__((mode(TI)));

typedef struct {
    int w;
    int unk4;
    void *data;
} RotTrack;

extern int func_00031438(void *out, int type, void *data, int frame);

static inline void lerp4(void *out, void *a, void *b, float t)
{
    __asm__ __volatile__("mfc1 $8, %3\n"
                         "qmtc2.ni $8, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyzw ACC, vf5, vf7x\n"
                         "vmaddw.xyzw vf9, vf6, vf8w\n"
                         "sqc2 vf9, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b), "f"(t) : "$8", "memory");
}

static inline float dot4(void *a, void *b)
{
    float r;

    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x0(%2)\n"
                         "vmul.xyzw vf15, vf14, vf15\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "qmfc2.ni $2, vf15\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline void scale4(void *v, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v), "r"(s) : "memory");
}

static inline int getRot(void *out, int type, void **data, int frame)
{
    if (*data != 0)
        return func_00031438(out, type, *data, frame);
    return 0;
}

static void func_00039FA8(void *out, RotTrack *trk, int i0, int i1, float frac)
{
    s128 v[2];
    s128 tmp[1];
    union { float f; int i; } d[2];

    if (frac == 0.0f) {
        getRot(out, (trk->w >> 8) & 0xFF, &trk->data, i0);
    } else if (frac < 0.5f) {
        getRot(&v[0], (trk->w >> 8) & 0xFF, &trk->data, i0);
        getRot(&v[1], (trk->w >> 8) & 0xFF, &trk->data, i1);
        tmp[0] = v[0];
        d[0].f = dot4(&v[1], tmp);
        if (d[0].i < 0)
            scale4(tmp, -1.0f);
        lerp4(out, &v[1], tmp, frac);
    } else {
        getRot(&v[0], (trk->w >> 8) & 0xFF, &trk->data, i0);
        getRot(&v[1], (trk->w >> 8) & 0xFF, &trk->data, i1);
        tmp[0] = v[0];
        d[1].f = dot4(&v[1], tmp);
        if (d[1].i < 0)
            scale4(tmp, -1.0f);
        lerp4(out, &v[1], tmp, frac);
    }
}
