typedef float Vec4[4] __attribute__((aligned(16)));
typedef int u128 __attribute__((mode(TI)));

extern char ZUnitVector[];
extern int calcAttainPosForAttainRange(char *, float *, float *, float *, void *, int, int);
extern float iosGetATan2fExact(float, float);

static inline void vecSub(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vecAdd(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline float distXZ(void *a, void *b)
{
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "vsqrt Q, vf7x\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2", "memory");
    return d;
}

static inline void vecNormalize(void *d, void *s)
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
                         : : "r"(d), "r"(s) : "memory");
}

static inline void applyMatrix(void *d, void *m, void *v)
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
                         : : "r"(d), "r"(m), "r"(v) : "memory");
}

static inline float lengthXYZ(void *v)
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
                         : "=f"(len) : "r"(v) : "$2", "memory");
    return len;
}

static inline void vecUnit(void *d)
{
    __asm__ __volatile__("sqc2 $vf0, 0x0(%0)
" : : "r"(d) : "memory");
}

static void func_00109028(char *w)
{
    Vec4 d0, d1, d2, t, p, q, r;
    float a;

    *(int *)(w + 0x144) = 0;
    vecUnit(w + 0x150);
    applyMatrix(t, w + 0x20, *(char **)(w + 0x18) + 0x30);
    t[1] = 0.0f;
    *(float *)(w + 0x140) = lengthXYZ(t);
    if (*(void **)(w + 0xC) == 0)
        return;
    if (*(void **)(w + 0x10) != 0) {
        *(u128 *)(w + 0x120) = **(u128 **)(w + 0xC);
        vecSub(d0, w + 0x120, *(char **)(w + 4) + 0x30);
        vecSub(d1, *(void **)(w + 0x10), *(void **)(w + 0xC));
    } else {
        if (calcAttainPosForAttainRange(w, r, p, q, *(void **)(w + 0xC), 0, 0)) {
            *(int *)(w + 0x144) = 1;
            *(u128 *)(w + 0x150) = *(u128 *)q;
            *(u128 *)(w + 0x120) = *(u128 *)p;
        } else {
            *(u128 *)(w + 0x120) = **(u128 **)(w + 0xC);
            *(u128 *)(w + 0x150) = *(u128 *)(*(char **)(w + 4) + 0xB0);
            __asm__ __volatile__("" ::: "memory");
            *(int *)(w + 0x144) = *(int *)(*(char **)(w + 4) + 0xA8);
        }
        vecSub(d0, w + 0x120, *(void **)(*(char **)(w + 0x18) + 0x134));
        *(u128 *)d1 = *(u128 *)d0;
    }
    d0[3] = 1.0f;
    d1[3] = 1.0f;
    vecNormalize(d0, d0);
    vecNormalize(d1, d1);
    vecAdd(d2, d0, d1);
    d2[3] = 1.0f;
    vecNormalize(d2, d2);
    applyMatrix(w + 0xE0, w + 0x20, d2);
    applyMatrix(w + 0xD0, w + 0x20, d0);
    applyMatrix(w + 0xF0, w + 0x20, d1);
    applyMatrix(w + 0x100, w + 0x20, w + 0x120);
    applyMatrix(w + 0x110, w + 0x20, *(void **)(*(char **)(w + 0x18) + 0x134));
    *(float *)(w + 0xE4) = 0.0f;
    *(float *)(w + 0xD4) = 0.0f;
    *(float *)(w + 0xF4) = 0.0f;
    vecNormalize(w + 0xE0, w + 0xE0);
    vecNormalize(w + 0xD0, w + 0xD0);
    vecNormalize(w + 0xF0, w + 0xF0);
    a = iosGetATan2fExact(*(float *)(w + 0xE0), *(float *)(w + 0xE8));
    *(float *)(w + 0x130) = iosGetATan2fExact(*(float *)(w + 0xD0), *(float *)(w + 0xD8));
    *(float *)(w + 0x134) = iosGetATan2fExact(*(float *)(w + 0xF0), *(float *)(w + 0xF8));
    *(float *)(w + 0x138) = a - *(float *)(w + 0x130);
    *(float *)(w + 0x13C) = distXZ(w + 0x110, w + 0x100);
}
