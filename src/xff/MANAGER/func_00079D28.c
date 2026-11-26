typedef long long s64;
typedef unsigned long long u64;
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; u64 d; float f; } U;
#define ST(T, a) (((U *)(a))->T)

extern void LoopExecPreLightColMan(void);
extern void LoopExecAfterLightColMan(void);
extern char *iosgluGetCameraContext(void);
extern void SetCameraReverbFlag(void *);
extern int *GetFirstSortObj(void *);
extern int *GetNextSortObj(void *, int *);
extern char *GetLayoutClass(int);
extern char *GetGeoDispClass(int);
extern void iosCopyMatrix(void *, void *);
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) V4;
typedef union { char *p; float f; int i; u64 d; s128 q; } UP;
#define PTR(a) (((UP *)(a))->p)

extern char *GetLayoutClass(int);
extern char *GetCharacterClass(int);
extern char *iosgluGetCameraContext(void);
extern float *getSpecularity(void);
extern float iosCalcFColorToBrightness(void *);
extern void iosCopyMatrix(void *, void *);
extern void iosInverseMatrix(void *, void *);
extern void iosTransposeMatrix(void *, void *);

static inline void applyMatrix(void *out, void *mat, void *in)
{
    __asm__ __volatile__(
        "lqc2 vf8, 0x0(%2)\n"
        "lqc2 vf14, 0x0(%1)\n"
        "lqc2 vf15, 0x10(%1)\n"
        "lqc2 vf16, 0x20(%1)\n"
        "lqc2 vf17, 0x30(%1)\n"
        "vmulax.xyzw ACC, vf14, vf8x\n"
        "vmadday.xyzw ACC, vf15, vf8y\n"
        "vmaddaz.xyzw ACC, vf16, vf8z\n"
        "vmaddw.xyzw vf10, vf17, vf8w\n"
        "sqc2 vf10, 0x0(%0)\n"
        : : "r"(out), "r"(mat), "r"(in) : "memory");
}

static inline float innerProduct(void *a, void *b)
{
    float dot;
    __asm__ __volatile__(
        "lqc2 vf5, 0x0(%1)\n"
        "lqc2 vf6, 0x0(%2)\n"
        "vaddw.x vf7, vf0, vf0w\n"
        "vmul.xyz vf6, vf5, vf6\n"
        "vaddax.x ACC, vf0, vf6x\n"
        "vmadday.x ACC, vf7, vf6y\n"
        "vmaddz.x vf6, vf7, vf6z\n"
        "qmfc2.ni $2, vf6\n"
        "mtc1 $2, %0\n"
        : "=f"(dot) : "r"(a), "r"(b) : "$2");
    return dot;
}

#define DD PTR(c + 0x144)
#define CC PTR(DD + 0xC)

static void func_00079788(int obj, char *unused)
{
    float m[4][4] __attribute__((aligned(16)));
    V4 v;
    V4 t;
    char *c;
    u64 fl;

    c = GetLayoutClass(obj);
    fl = *(u64 *)(DD + 0x260);
    if (fl & 4) {
        if (fl & 8) {
            iosCopyMatrix(m, *(void **)(c + 0x158));
            iosInverseMatrix(m, m);
            ((UP *)&v)->q = ((UP *)(CC + 0x10))->q;
            v.w = 1.0f;
            applyMatrix(&v, m, &v);
            *(float *)(CC + 0x10) = v.x;
            *(float *)(CC + 0x14) = v.y;
            *(float *)(CC + 0x18) = v.z;
        } else {
            __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(CC + 0x50) : "memory");
            *(int *)(CC + 0x1C) = 0;
        }
    } else {
        float one = 1.0f;
        char *cam;
        float *spec;
        float dot;
        t.x = *(float *)(PTR(c + 0x140) + 0x40);
        t.y = *(float *)(PTR(c + 0x140) + 0x50);
        t.z = *(float *)(PTR(c + 0x140) + 0x60);
        t.w = one;
        v = t;
        cam = iosgluGetCameraContext();
        spec = getSpecularity();
        *(float *)(CC + 0xD4) = *spec * iosCalcFColorToBrightness(PTR(c + 0x140) + 0xB0);
        dot = innerProduct(cam + 0x150, &v);
        *(float *)(CC + 0xD8) = *(float *)(CC + 0xD4) * ((dot + one) * 0.25f + 0.5f);
        {
            char *ch = GetCharacterClass(obj);
            if (ch != 0 && *(short *)(ch + 0x370) == 4) {
                *(int *)(CC + 0x1C) = 0;
                *(float *)(CC + 0x2C) = one;
                *(int *)(CC + 0x3C) = 0;
            }
        }
        iosCopyMatrix(m, iosgluGetCameraContext() + 0x1A0);
        __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(m[3]) : "memory");
        iosTransposeMatrix(m, m);
        __asm__ __volatile__(
            "lqc2 vf14, 0x0(%0)\n"
            "lqc2 vf15, 0x10(%0)\n"
            "lqc2 vf16, 0x20(%0)\n"
            "lqc2 vf17, 0x30(%0)\n"
            "lqc2 vf24, 0x0(%1)\n"
            "lqc2 vf25, 0x10(%1)\n"
            "lqc2 vf26, 0x20(%1)\n"
            "lqc2 vf27, 0x30(%1)\n"
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
            : : "r"(CC + 0x10), "r"(m) : "memory");
        *(float *)(CC + 0x1C) *= -*(float *)(DD + 0x288) * *(float *)(DD + 0x28C);
        *(float *)(CC + 0x2C) *= -*(float *)(DD + 0x288) * *(float *)(DD + 0x28C);
        *(float *)(CC + 0x3C) *= -*(float *)(DD + 0x288) * *(float *)(DD + 0x28C);
    }
}
#undef DD
#undef CC

typedef void (*DispFn)(int);

static void func_00079D28(void *list)
{
    int *s;

    LoopExecPreLightColMan();
    SetCameraReverbFlag(iosgluGetCameraContext() + 0x140);

    for (s = GetFirstSortObj(list); s != 0; s = GetNextSortObj(list, s)) {
        int obj = *s;
        char *lc = GetLayoutClass(obj);
        if (lc != 0) {
            char *l = *(char **)(lc + 0x140);
            if ((*(u64 *)(*(char **)(lc + 0x144) + 0x260) & 2) && l != 0 && *(DispFn *)(l + 0xE0) != 0)
                (*(DispFn *)(l + 0xE0))(obj);
        } else {
            char *g = GetGeoDispClass(obj);
            if (g != 0 && *(DispFn *)(g + 0xE0) != 0)
                (*(DispFn *)(g + 0xE0))(obj);
        }
    }

    for (s = GetFirstSortObj(list); s != 0; s = GetNextSortObj(list, s)) {
        int obj = *s;
        float f;
        char *c = GetLayoutClass(obj);
        if (c != 0) {
            char *d = *(char **)(c + 0x144);
            char *l = *(char **)(c + 0x140);
            if ((*(u64 *)(d + 0x260) & 2) && l != 0 && *(DispFn *)(l + 0xE0) != 0 && *(int *)(c + 0x198) == 0)
                func_00079788(obj, d);
            d = *(char **)(c + 0x144);
            f = *(float *)(*(char **)(*(char **)(*(char **)d + 0x20) + 0x8) + 0x2C);
            if (f != 1.0f) {
                char *v = *(char **)(d + 0xC) + 0x80;
                __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nqmtc2.ni %1, vf6\nvmulx.xyzw vf5, vf5, vf6x\nsqc2 vf5, 0x0(%0)\n" : : "r"(v), "r"(f) : "memory");
            }
        }
    }

    for (s = GetFirstSortObj(list); s != 0; s = GetNextSortObj(list, s)) {
        char *c = GetLayoutClass(*s);
        char *p;
        char *l;
        if (c == 0)
            continue;
        l = *(char **)(c + 0x140);
        if ((*(u64 *)(*(char **)(c + 0x144) + 0x260) & 2) && l != 0 && *(DispFn *)(l + 0xE0) != 0 && *(int *)(c + 0x198) != 0) {
            p = GetLayoutClass(*(int *)(c + 0x198));
            ST(q, *(char **)(c + 0x140) + 0x10) = *(s128 *)(*(char **)(p + 0x140) + 0x10);
            ST(d, *(char **)(c + 0x140) + 0xC0) = (*(u64 *)(*(char **)(c + 0x140) + 0xC0) & ~1ULL) | (*(unsigned char *)(*(char **)(p + 0x140) + 0xC0) & 1);
            ST(d, *(char **)(c + 0x144) + 0x260) = (*(u64 *)(*(char **)(c + 0x144) + 0x260) & ~8ULL) | ((((unsigned short)(*(u64 *)(*(char **)(p + 0x144) + 0x260) >> 3)) & 1) << 3);
            iosCopyMatrix(*(char **)(*(char **)(c + 0x144) + 0xC) + 0x50, *(char **)(*(char **)(p + 0x144) + 0xC) + 0x50);
            iosCopyMatrix(*(char **)(*(char **)(c + 0x144) + 0xC) + 0x10, *(char **)(*(char **)(p + 0x144) + 0xC) + 0x10);
            ST(f, *(char **)(*(char **)(c + 0x144) + 0xC) + 0xD4) = *(float *)(*(char **)(*(char **)(p + 0x144) + 0xC) + 0xD4);
            ST(f, *(char **)(*(char **)(c + 0x144) + 0xC) + 0xD8) = *(float *)(*(char **)(*(char **)(p + 0x144) + 0xC) + 0xD8);
        }
    }

    LoopExecAfterLightColMan();
}
