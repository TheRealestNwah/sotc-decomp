#ifdef NONMATCHING /* 5 diffs: the delay-slot argument copy for the first func_000E5EA0 call is hoisted from the wrong branch */
typedef int s128 __attribute__((mode(TI)));

extern int GetAnimationClassObjectAnimation(void *, float *, void *, int);
extern void GetEulerYXZFromQuaternion(void *, void *);
extern float func_000E5EA0(void *, int);

static inline void scaleXYZ(void *v, float s)
{
    __asm__ __volatile__(
        "lqc2 vf5, 0x0(%0)\n"
        "qmtc2.ni %1, vf6\n"
        "vmulx.xyz vf5, vf5, vf6x\n"
        "sqc2 vf5, 0x0(%0)\n"
        :
        : "r"(v), "r"(s)
        : "memory");
}

static inline int flagBit(int *p)
{
    return ((unsigned int *)p)[4] >> 11 & 1;
}

static void func_000E74B8(char *out, int **anim, int a, int b)
{
    char buf[0x60] __attribute__((aligned(16)));
    s128 quat;

    float scale;
    register char *o10 __asm__("$17") = out + 0x10;

    if ((*anim)[0x17] == 0)
        scale = func_000E5EA0(anim, a);
    else
        scale = func_000E5EA0(anim, b);
    GetAnimationClassObjectAnimation(buf, (float *)(anim + 1), (void *)anim[0x11], 0);
    *(int *)(out + 8) = *(int *)(buf + 0x40);
    quat = *(s128 *)(buf + 0x20);
    GetEulerYXZFromQuaternion(o10, &quat);
    *(s128 *)(out + 0x30) = *(s128 *)(buf + 0x10);
    if (scale != 1.0f) {
        scaleXYZ(o10, scale);
        scaleXYZ(out + 0x30, scale);
    }
    { register int w __asm__("$2") = *(int *)(buf + 0x48);
    *(int *)(out + 0x80) = w; }
    { register int one __asm__("$4") = 1;
    if (flagBit(*anim) == one) {
        *(float *)(out + 0x84) = *(float *)(buf + 0x30);
        *(float *)(out + 0x88) = *(float *)(buf + 0x34);
    } else {
        *(float *)(out + 0x84) = *(float *)(buf + 0x34);
        *(float *)(out + 0x88) = *(float *)(buf + 0x30) / *(float *)(buf + 0x34);
    }
    }
    *(float *)(out + 0x8C) = *(float *)(buf + 0x38);
}
#endif
