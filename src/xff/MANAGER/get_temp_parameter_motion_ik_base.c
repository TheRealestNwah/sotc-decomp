#ifdef NONMATCHING /* 25 diffs: word count matches (141); idx/idx*64 temps land in a2/a1 instead of a1/a2, else-branch v1 load order; explicit lw asm adds a nop (worse) */
typedef int s128 __attribute__((mode(TI)));

extern int DldSysUndefSymbol;
extern void GAMEUTIL_convert_from_lw_to_game_coord(void *);

static inline char *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;

    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != (char *)DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}

static inline void quatMul(float *dst, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
                         "lqc2 vf12, 0x0(%1)\n"
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
                         "sqc2 vf13, 0x0(%2)\n"
                         : : "r"(a), "r"(b), "r"(dst) : "memory");
}

void get_temp_parameter_motion_ik_base(float *out, int **ctx)
{
    float tmp[4];
    int *a3 = *ctx;
    char *s1 = resourceData(*(unsigned int **)((char *)a3 + 0x18));
    int idx;
    int a2;
    char *v1;

    if (*(int *)(s1 + 0x10) == 0) {
        idx = *(int *)((char *)a3 + 0x14);
        __asm__ __volatile__("lqc2 vf11, 0x0(%0)\n"
                             "vsubw.x vf5, vf0, vf0w\n"
                             "vmulx.xyz vf11, vf11, vf5x\n"
                             "sqc2 vf11, 0x0(%1)\n"
                             : : "r"(idx * 16 + *(int *)((char *)a3 + 4)), "r"(tmp) : "memory");
        quatMul(out, (float *)(idx * 16 + *(int *)((char *)a3 + 0xC)), tmp);
        a2 = idx * 64;
        quatMul(out, out, (float *)(a2 + *(int *)(*(int *)((char *)a3 + 0x10) + 8) + 0x20));
        v1 = *(char **)((char *)a3 + 8);
    } else {
        idx = *(int *)((char *)a3 + 0x14);
        *(s128 *)out = *(s128 *)(idx * 16 + *(int *)((char *)a3 + 0xC));
        a2 = idx * 64;
        v1 = *(char **)((char *)a3 + 8);
    }
    *(s128 *)(out + 4) = *(s128 *)(a2 + v1 + 0x30);
    out[8] = *(float *)(s1 + 0x18);
    out[9] = *(float *)(s1 + 0x1C);
    out[10] = *(float *)(s1 + 0x20);
    out[11] = 1.0f;
    out[12] = *(float *)(s1 + 0x24);
    out[13] = *(float *)(s1 + 0x28);
    out[14] = *(float *)(s1 + 0x2C);
    out[15] = 0;
    out[16] = *(float *)(s1 + 0x30);
    out[17] = *(float *)(s1 + 0x34);
    out[18] = *(float *)(s1 + 0x38);
    out[19] = 0;
    GAMEUTIL_convert_from_lw_to_game_coord(out + 8);
    GAMEUTIL_convert_from_lw_to_game_coord(out + 12);
    GAMEUTIL_convert_from_lw_to_game_coord(out + 16);
    out[20] = *(float *)(s1 + 0x60) * 0.017453293f;
    out[21] = *(float *)(s1 + 0x64) * 0.017453293f;
    out[22] = *(float *)(s1 + 0x68) * 0.017453293f;
    out[23] = *(float *)(s1 + 0x6C) * 0.017453293f;
    out[24] = *(float *)(s1 + 0x70) * 0.017453293f;
    out[25] = *(float *)(s1 + 0x74) * 0.017453293f;
}
#endif
