typedef int s128 __attribute__((mode(TI)));

extern char ZeroVector[];
extern char All1Vector[];
extern float iosGetRandom(void);

#ifdef NONMATCHING /* 21 diffs: the nine-entry jump table, register use and VU0 sequence match; gcc hoists the 0x26C/0x270 stores ahead of the float math where the original leaves them in the branch delay slots */
static void func_0009D208(char *c)
{
    char *p;
    float f20;
    float r;
    int mode;
    int prev = *(int *)(c + 0x1A8);

    mode = *(int *)(c + 0x1AC);
    if (prev == mode)
        return;
    *(int *)(c + 0x490) = 1;
    *(int *)(c + 0x1C4) = 0;
    *(int *)(c + 0x1CC) = 0;
    switch (mode) {
    case 0:
        break;
    case 1:
        r = iosGetRandom();
        p = *(char **)(c + 0x20);
        *(float *)(c + 0x1C0) = *(float *)(p + 0x38) + *(float *)(p + 0x3C) * r;
        *(int *)(c + 0x270) = 0;
        *(s128 *)(c + 0x4D0) = *(s128 *)ZeroVector;
        *(int *)(c + 0x26C) = 0;
        break;
    case 2:
    case 3:
    case 7:
        *(int *)(c + 0x270) = 0;
        *(s128 *)(c + 0x4D0) = *(s128 *)ZeroVector;
        *(int *)(c + 0x26C) = 0;
        break;
    case 4:
    case 5:
        *(int *)(c + 0x1C8) = 0;
        r = iosGetRandom();
        p = *(char **)(c + 0x20);
        *(float *)(c + 0x1C0) = *(float *)(p + 0x18) + *(float *)(p + 0x1C) * r;
        break;
    case 6:
        *(int *)(c + 0x270) = 0;
        *(int *)(c + 0x1C0) = 0;
        *(int *)(c + 0x26C) = 0;
        break;
    case 8:
        *(int *)(c + 0x1C0) = 0;
        if (*(int *)(c + 0x2C) != 0 || *(int *)(c + 0x34) == 2) {
            *(s128 *)(c + 0x4D0) = *(s128 *)ZeroVector;
            break;
        }
        f20 = *(float *)(*(char **)(c + 0x20) + 0x14);
        c += 0x4D0;
        *(float *)(c + 0) = iosGetRandom();
        *(float *)(c + 4) = iosGetRandom();
        *(float *)(c + 8) = iosGetRandom();
        *(float *)(c + 12) = iosGetRandom();
        {
            float two = 2.0f;
            __asm__ __volatile__("mfc1 $2, %1\n"
                                 "lqc2 vf5, 0x0(%0)\n"
                                 "qmtc2.ni $2, vf6\n"
                                 "vmulx.xyzw vf5, vf5, vf6x\n"
                                 "sqc2 vf5, 0x0(%0)\n"
                                 : : "r"(c), "f"(two) : "$2", "memory");
        }
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vsub.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf5, 0x0(%0)\n"
                             "vmul.xyz vf7, vf5, vf5\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             "vrsqrt Q, vf0w, vf7w\n"
                             "vwaitq\n"
                             "vmulq.xyz vf5, vf5, Q\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(c), "r"(All1Vector) : "memory");
        __asm__ __volatile__("mfc1 $2, %1\n"
                             "lqc2 vf5, 0x0(%0)\n"
                             "qmtc2.ni $2, vf6\n"
                             "vmulx.xyzw vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(c), "f"(f20) : "$2", "memory");
        break;
    default:
        break;
    }
}
#endif
