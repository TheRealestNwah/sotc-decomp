typedef int s128 __attribute__((mode(TI)));

extern char *GetCharacterClass(void *);

void estimateAttainPos2(char *attain, float *out, float time)
{
    void *target = *(void **)(*(char **)(attain + 4) + 0x94);

    if (target != 0) {
        char *chara = GetCharacterClass(target);
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "qmtc2.ni %2, vf6\n"
                             "vmulx.xyz vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(out), "r"(chara + 0x30), "r"(time) : "memory");
        __asm__ __volatile__(".set noreorder\n"
                             "lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vadd.xyzw vf7, vf5, vf6\n"
                             "sqc2 vf7, 0x0(%0)\n"
                             ".set reorder\n"
                             : : "r"(out), "r"(out), "r"(*(float **)(chara + 0x134)) : "memory");
    } else {
        *(s128 *)out = **(s128 **)(attain + 0xC);
    }
    out[3] = 1.0f;
}
