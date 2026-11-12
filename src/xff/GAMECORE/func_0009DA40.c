typedef int s128 __attribute__((mode(TI)));

static inline float distSq(char *a, char *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

#ifdef NONMATCHING /* 17 diffs: layout matches; near3 operand pointers are allocated a1/a0/v1 in the original and v1/a1/a0 here, and the original re-reads c+0x40/c+0x4F0 by offset where ours reuses the near3 address registers */
static inline int near3(char *c)
{
    float r = *(float *)(*(char **)(c + 0x20) + 0x2C);

    return distSq(c + 0x40, c + 0x4F0) <= r * r;
}

static void func_0009DA40(char *c, char *out0)
{
    register char *out __asm__("$7") = out0;
    float r;
    float off;

    switch (*(int *)(c + 0x1AC)) {
    case 1:
    case 2:
        *(s128 *)out = *(s128 *)(c + 0x4F0);
        return;
    case 3:
        if (near3(c)) {
            *(int *)(c + 0x26C) = 1;
            *(int *)(c + 0x270) = 1;
            *(s128 *)out = *(s128 *)(c + 0x40);
            off = 0.5f;
            goto add;
        }
        *(int *)(c + 0x26C) = 0;
        *(s128 *)out = *(s128 *)(c + 0x4F0);
        return;
    case 4:
    case 5:
        break;
    case 6:
        if (near3(c)) {
            *(int *)(c + 0x270) = 1;
            *(s128 *)out = *(s128 *)(c + 0x40);
            off = 1.0f;
        add:
            *(float *)(out + 4) = *(float *)(out + 4) + off;
            return;
        }
        break;
    }
    *(s128 *)out = *(s128 *)(c + 0x4A0);
}
#endif
