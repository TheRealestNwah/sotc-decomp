extern char D_001370F0[];

static void func_000C7048(char *out, char *in, char *p)
{
    char *c = p + 0x30;
    int i;

    for (i = 0; i < 8; i++) {
        __asm__ __volatile__("lqc2 vf8, 0x0(%3)\n"
                             "lqc2 vf9, 0x0(%1)\n"
                             "lqc2 vf14, 0x0(%2)\n"
                             "lqc2 vf15, 0x10(%2)\n"
                             "lqc2 vf16, 0x20(%2)\n"
                             "lqc2 vf17, 0x30(%2)\n"
                             "vmulax.xyzw ACC, vf14, vf8x\n"
                             "vmadday.xyzw ACC, vf15, vf8y\n"
                             "vmaddaz.xyzw ACC, vf16, vf8z\n"
                             "vmaddw.xyzw vf10, vf17, vf8w\n"
                             "vdiv Q, vf0w, vf10w\n"
                             "vwaitq\n"
                             "vmulq.xyz vf10, vf10, Q\n"
                             "vadd.xy vf10, vf10, vf9\n"
                             "sqc2 vf10, 0x0(%0)\n"
                             : : "r"(out + i * 16), "r"(c), "r"(D_001370F0), "r"(in + i * 16) : "memory");
    }
}
