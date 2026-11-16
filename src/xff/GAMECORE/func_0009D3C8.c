typedef int s128 __attribute__((mode(TI)));

typedef struct {
    long a, b, c, d;
} B32;

extern char All1Vector[];
extern void *isysGetThisSubThread(void);
extern void Kite_GetPassageWork(void *, int, void *, void *, int);
extern float iosGetRandom(void);
extern void func_0009CF80(char *);
extern void func_0009D088(char *);
extern void func_0009D208(char *);

static void func_0009D3C8(char *w)
{
    void *thread;
    char *a0;
    char *a1;
    char *t1;
    char *s0;
    int v;
    float f20;
    float r;
    int bits;
    int pw;

    thread = isysGetThisSubThread();
    *(s128 *)(w + 0x350) = *(s128 *)(w + 0x4D0);
    if (*(int *)(w + 0x2C) != 0 || *(int *)(w + 0x34) == 2) {
        Kite_GetPassageWork(thread, *(int *)(w + 0x278), w + 0x280, w + 0x280, 1);
    } else {
        t1 = *(char **)(w + 0x30);
        pw = *(int *)(t1 + 0x278);
        *(B32 *)(w + 0x310) = *(B32 *)(t1 + 0x4F0);
        *(B32 *)(w + 0x330) = *(B32 *)(t1 + 0x530);
        Kite_GetPassageWork(thread, pw, t1 + 0x280, w + 0x280, *(unsigned int *)(w + 0x494) < 1);
    }
    a0 = w + 0x2B0;
    if (*(int *)(a0 + 0x10) != -1)
        *(B32 *)(w + 0x550) = *(B32 *)a0;
    a1 = w + 0x290;
    if (*(int *)(a1 + 0x10) != -1) {
    *(int *)(w + 0x490) = 1;
    *(B32 *)(w + 0x510) = *(B32 *)a1;
    func_0009CF80(w);
    func_0009D088(w);
    func_0009D208(w);
    switch (*(unsigned int *)(w + 0x1AC)) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 7:
    case 8:
        break;
    case 4:
    case 5:
    case 6:
        if (*(float *)(w + 0x1CC) >= *(float *)(w + 0x1C8)) {
            s0 = w + 0x4D0;
            r = iosGetRandom();
            *(float *)(w + 0x1C8) = *(float *)(*(char **)(w + 0x20) + 0x24) * r;
            f20 = *(float *)(*(char **)(w + 0x20) + 0x20);
            *(float *)(s0 + 0) = iosGetRandom();
            *(float *)(s0 + 4) = iosGetRandom();
            *(float *)(s0 + 8) = iosGetRandom();
            *(float *)(s0 + 0xC) = iosGetRandom();
            r = 2.0f;
            __asm__ __volatile__("mfc1 %0, %1" : "=r"(bits) : "f"(r));
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nqmtc2.ni %1, vf6\nvmulx.xyzw vf5, vf5, vf6x\nsqc2 vf5, 0x0(%0)\n"
                                 : : "r"(s0), "r"(bits) : "memory");
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nlqc2 vf6, 0x0(%1)\nvsub.xyz vf5, vf5, vf6\nsqc2 vf5, 0x0(%0)\n"
                                 : : "r"(s0), "r"(All1Vector) : "memory");
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "vmul.xyz vf7, vf5, vf5\n"
                                 "vmulax.w ACC, vf0, vf7x\n"
                                 "vmadday.w ACC, vf0, vf7y\n"
                                 "vmaddz.w vf7, vf0, vf7z\n"
                                 "vrsqrt Q, vf0w, vf7w\n"
                                 "vwaitq\n"
                                 "vmulq.xyz vf5, vf5, Q\n"
                                 "sqc2 vf5, 0x0(%0)\n"
                                 : : "r"(s0) : "memory");
            __asm__("mfc1 %0, %1" : "=r"(bits) : "f"(f20));
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nqmtc2.ni %1, vf6\nvmulx.xyzw vf5, vf5, vf6x\nsqc2 vf5, 0x0(%0)\n"
                                 : : "r"(s0), "r"(bits) : "memory");
            *(int *)(w + 0x1CC) = 0;
        }
        break;
    }
    if (*(unsigned int *)(w + 0x1AC) == 8) {
        if (*(int *)(w + 0x500) != *(int *)(w + 0x520))
            *(B32 *)(w + 0x570) = *(B32 *)(w + 0x4F0);
        *(B32 *)(w + 0x4F0) = *(B32 *)(w + 0x510);
        *(B32 *)(w + 0x530) = *(B32 *)(w + 0x550);
    }
    if (*(int *)(w + 0x500) == *(int *)(w + 0x520)) {
        if (*(int *)(w + 0x540) != *(int *)(w + 0x560))
            *(B32 *)(w + 0x530) = *(B32 *)(w + 0x550);
    }
    } else {
        *(int *)(w + 0x490) = 0;
        *(int *)(w + 0x504) = 0;
    }
}
