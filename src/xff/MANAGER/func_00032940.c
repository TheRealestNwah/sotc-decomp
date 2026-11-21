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
    __asm__ __volatile__("mfc1 $2, %1\n"
                         "lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni $2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v), "f"(s) : "$2", "memory");
}

typedef struct {
    char pad0[8];
    unsigned char *types;
    char padc[4];
    void **data;
} Tracks;

static inline void qlerp(void *out, void *a, void *b, s128 *tmp, float t)
{
    union { float f; int i; } d;

    tmp[0] = *(s128 *)b;
    d.f = dot4(a, tmp);
    if (d.i < 0)
        scale4(tmp, -1.0f);
    lerp4(out, a, tmp, t);
}

static void func_00032940(void *out, Tracks *trk, int idx, int i0, int i1, float t)
{
    s128 v[2];
    s128 tmp[1];

    if (t == 0.0f) {
        func_00031438(out, trk->types[idx], trk->data[idx], i0);
    } else if (t < 0.5f) {
        func_00031438(&v[0], trk->types[idx], trk->data[idx], i0);
        func_00031438(&v[1], trk->types[idx], trk->data[idx], i1);
        qlerp(out, &v[0], &v[1], tmp, 1.0f - t);
    } else {
        func_00031438(&v[0], trk->types[idx], trk->data[idx], i0);
        func_00031438(&v[1], trk->types[idx], trk->data[idx], i1);
        qlerp(out, &v[1], &v[0], tmp, t);
    }
}
