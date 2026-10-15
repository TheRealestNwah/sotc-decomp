typedef int s128 __attribute__((mode(TI)));

/* The empty noreorder block stops the assembler from moving the final sqc2
   into the return delay slot, as in the original. */
void GetDirColorFromWorkLight(s128 *dir, float *color, char *w)
{
    float s = 0.0039215684f;
    *dir = *(s128 *)(w + 0x10);
    __asm__ __volatile__("lqc2 vf05, 0(%1)\n"
                         "qmtc2 %2, vf06\n"
                         "vmulx.xyz vf05, vf05, vf06x\n"
                         "sqc2 vf05, 0(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(color), "r"(w + 0x20), "r"(s) : "memory");
}
