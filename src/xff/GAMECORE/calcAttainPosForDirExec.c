extern char *GetCharacterClass(void *);

void calcAttainPosForDirExec(void *obj, char *w, float *target, float *out)
{
    char *c = GetCharacterClass(obj);
    char *r = w + 0x3E0;
    float d[4] __attribute__((aligned(16)));
    float len;

    len = *(float *)(r + 0x8);
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(target), "r"(*(void **)(c + 0x134)) : "memory");
    d[1] = 0.0f;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d) : "memory");
    len = len + (*(float *)(r + 0x10) + *(float *)(r + 0x14)) * 0.5f;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(len) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(out), "r"(d), "r"(*(void **)(c + 0x134)) : "memory");
    out[1] = out[1] + *(float *)(r + 0x4);
    out[3] = 1.0f;
}
