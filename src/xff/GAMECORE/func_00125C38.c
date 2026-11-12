typedef int s128 __attribute__((mode(TI)));

extern char *GetCharacterClass(int);
extern char *GetLayoutClass(int);
extern int func_00127A48(int, char *);
extern void func_00127AC8(float *, void *, float *, int, char *);

static inline void quatMul(void *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                         "lqc2 vf12, 0x0(%2)\n"
                         "vmul.xyzw vf13, vf11, vf12\n"
                         "vaddy.x vf13, vf13, vf13y\n"
                         "vaddz.x vf13, vf13, vf13z\n"
                         "vsubx.w vf13, vf13, vf13x\n"
                         "vmulw.xyz vf14, vf12, vf11w\n"
                         "vmulw.xyz vf15, vf11, vf12w\n"
                         "vopmula.xyz ACC, vf12, vf11\n"
                         "vopmsub.xyz vf16, vf11, vf12\n"
                         "vadd.xyz vf13, vf14, vf15\n"
                         "vadd.xyz vf13, vf13, vf16\n"
                         "sqc2 vf13, 0x0(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void normalize4(void *v)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%0)\n"
                         "vmul.xyzw vf15, vf14, vf14\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "vrsqrt Q, vf0w, vf15x\n"
                         "vwaitq\n"
                         "vmulq.xyzw vf15, vf14, Q\n"
                         "sqc2 vf15, 0x0(%0)\n"
                         : : "r"(v) : "memory");
}

#ifdef NONMATCHING /* 50 diffs: out/s1 swapped in $s0/$s1 and the $a0/$a1 node-pointer load order */
int func_00125C38(float *out, float *out2, int id, char *w)
{
    float tmp[4] __attribute__((aligned(16)));
    int chr = *(int *)w;
    int s1 = func_00127A48(id, w);

    if (s1 == -1) {
        s1 = id - 1;
        if (func_00127A48(s1, w) < 0)
            return 0;
        if (s1 < 0)
            return 0;
        *(s128 *)out = *(s128 *)(GetCharacterClass(chr) + 0x480);
        *(s128 *)out2 = **(s128 **)(GetLayoutClass(chr) + 0x134);
        return 1;
    }
    if (*(int *)(GetCharacterClass(chr) + 0x378) == s1) {
        quatMul(out, GetCharacterClass(chr) + 0x480, (s1 << 6) + *(char **)(*(char **)(w + 0x10) + 8) + 0x20);
        normalize4(out);
        func_00127AC8(out2, *(void **)(GetLayoutClass(chr) + 0x134), out, s1, w);
        return 1;
    }
    if (s1 < 0)
        return 0;
    if (s1 > 0 && (s1 & 0x10000))
        return 0;
    {
        char *a = *(char **)(w + 4) + (s1 << 4);
        char *b;
        __asm__ __volatile__("lqc2 vf11, 0x0(%1)\n"
                             "vsubw.x vf5, vf0, vf0w\n"
                             "vmulx.xyz vf11, vf11, vf5x\n"
                             "sqc2 vf11, 0x0(%0)\n"
                             : : "r"(tmp), "r"(a) : "memory");
        b = *(char **)(w + 0xC) + (s1 << 4);
        quatMul(out, b, tmp);
        quatMul(out, out, (s1 << 6) + *(char **)(*(char **)(w + 0x10) + 8) + 0x20);
        normalize4(out);
        *(s128 *)out2 = *(s128 *)((s1 << 6) + *(char **)(w + 8) + 0x30);
    }
    return 1;
}
#endif
