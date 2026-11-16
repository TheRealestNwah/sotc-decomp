#ifdef NONMATCHING /* 28 diffs: v0/v1 and f0-f3 temp numbering (pointer temps for src+0x10/buf, float temps in the scale step) */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

extern void iosIColToFvec(void *, int);

static inline void zero(s128 *v)
{
    __asm__ __volatile__("sq $0, 0(%0)" : : "r"(v) : "memory");
}

int func_0007B8D0(char *out, char *src, char *c)
{
    Vec4 buf[2];
    register char *s0 __asm__("$16");
    s128 v;
    float f0;
    float f1;
    float f2;
    float f3;
    int flags;

    if (out != 0) {
    *(int *)(out + 0x30) = 0;
    flags = *(int *)(src + 0x2C);
    if (flags & 0x12) {
        *(int *)(out + 0x30) = 8;
    } else if (flags & 4) {
        *(int *)(out + 0x30) = 8;
    } else if (*(int *)(c + 0x18) != 0) {
        *(int *)(out + 0x30) = 4;
        *(s128 *)out = *(s128 *)src;
        *(float *)(out + 0x3C) = *(float *)(src + 0x28);
    } else {
        *(int *)(out + 0x30) = 8;
    }
    flags = *(int *)(src + 0x2C);
    if (flags & 0x100) {
        *(int *)(out + 0x30) |= 0x100;
        flags = *(int *)(src + 0x2C);
    }
    if (flags & 0x1C) {
        __asm__ __volatile__("lqc2 vf4, 0x0(%0)\n"
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
                             "sqc2 vf6, 0x0(%1)\n"
                             : : "r"(src + 0x10), "r"(&buf[1]) : "memory");
    }
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%2)\n"
                         : : "r"(c), "r"(src), "r"(buf) : "memory");
    buf[0].i[3] = 0;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(buf) : "memory");
    if (*(int *)(src + 0x2C) & 4)
        v = buf[1].q;
    else
        v = buf[0].q;
    *(s128 *)(out + 0x10) = v;
    *(int *)(out + 0x34) = *(int *)(src + 0x30);
    s0 = out + 0x20;
    iosIColToFvec(s0, *(int *)(src + 0x3C));
    f0 = *(float *)(src + 0x24) * (1.0f - *(float *)(c + 0x10) / *(float *)(src + 0x28));
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(s0), "r"(f0) : "memory");
    *(float *)(out + 0x38) = *(float *)(c + 0x14);
    if (*(float *)(c + 0x1C) < *(float *)(src + 0x48)) {
        f0 = *(float *)(c + 0x20);
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "qmtc2.ni %1, vf6\n"
                             "vmulx.xyz vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(s0), "r"(f0) : "memory");
    }
    return 1;
    }
    return 0;
}
#endif
