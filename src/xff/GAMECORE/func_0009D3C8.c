/* Copies the passage work for this frame, refreshes the target passages and, in states 4 to 6, picks a new random wander direction when its timer runs out. */
typedef struct { int i[8]; } __attribute__((aligned(8))) Pass;
typedef int Vec __attribute__((mode(TI)));

extern void *isysGetThisSubThread(void);
extern void Kite_GetPassageWork(void *, int, void *, void *, int);
extern float iosGetRandom(void);
extern float All1Vector[];
extern void func_0009CF80(char *);
extern void func_0009D088(char *);
extern void func_0009D208(char *);

#define W(o) (*(int *)(w + (o)))
#define F(o) (*(float *)(w + (o)))
#define P(o) (*(Pass *)(w + (o)))

static inline void vecScaleW(float *dst, float *v, float s)
{
    __asm__ __volatile__("mfc1 $2, %2\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni $2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(v), "f"(s) : "$2", "memory");
}

static inline void vecSubXYZ(float *out, float *a, float *b)
{
    register float *bb asm("$2") = b;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(bb) : "memory");
}

static inline void vecNormalize(float *output, float *input)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf5, 0x0(%1)\n"
        "vmul.xyz vf7, vf5, vf5\n"
        "vmulax.w ACC, vf0, vf7x\n"
        "vmadday.w ACC, vf0, vf7y\n"
        "vmaddz.w vf7, vf0, vf7z\n"
        "vrsqrt Q, vf0w, vf7w\n"
        "vwaitq\n"
        "vmulq.xyz vf5, vf5, Q\n"
        "sqc2 vf5, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(output), "r"(input) : "memory");
}

static void func_0009D3C8(char *w)
{
    void *th = isysGetThisSubThread();
    Pass *a, *b;

    *(Vec *)(w + 0x350) = *(Vec *)(w + 0x4D0);
    if (W(0x2C) != 0 || W(0x34) == 2) {
        Kite_GetPassageWork(th, W(0x278), w + 0x280, w + 0x280, 1);
    } else {
        char *t = *(char **)(w + 0x30);
        int id = *(int *)(t + 0x278);
        P(0x310) = *(Pass *)(t + 0x4F0);
        P(0x330) = *(Pass *)(t + 0x530);
        Kite_GetPassageWork(th, id, t + 0x280, w + 0x280, W(0x494) == 0);
    }
    a = (Pass *)(w + 0x2B0);
    b = (Pass *)(w + 0x290);
    if (a->i[4] != -1)
        P(0x550) = *a;
    if (b->i[4] != -1) {
        W(0x490) = 1;
        P(0x510) = *b;
        func_0009CF80(w);
        func_0009D088(w);
        func_0009D208(w);
    switch (W(0x1AC)) {
    case 4:
    case 5:
    case 6:
        if (F(0x1CC) >= F(0x1C8)) {
            float *v = (float *)(w + 0x4D0);
            float len;
            F(0x1C8) = *(float *)(*(char **)(w + 0x20) + 0x24) * iosGetRandom();
            len = *(float *)(*(char **)(w + 0x20) + 0x20);
            v[0] = iosGetRandom();
            v[1] = iosGetRandom();
            v[2] = iosGetRandom();
            v[3] = iosGetRandom();
            vecScaleW(v, v, 2.0f);
            vecSubXYZ(v, v, All1Vector);
            vecNormalize(v, v);
            vecScaleW(v, v, len);
            F(0x1CC) = 0.0f;
        }
        break;
    case 0:
    case 1:
    case 2:
    case 3:
    case 7:
    case 8:
        break;
    }
    if (W(0x1AC) == 8) {
        if (W(0x500) != W(0x520))
            P(0x570) = P(0x4F0);
        P(0x4F0) = P(0x510);
        P(0x530) = P(0x550);
    }
    if (W(0x500) == W(0x520) && W(0x540) != W(0x560))
        P(0x530) = P(0x550);
    } else {
        W(0x490) = 0;
        W(0x504) = 0;
    }
}
