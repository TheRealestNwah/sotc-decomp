typedef int s128 __attribute__((mode(TI)));

void charrootdyn_getInterpPoint(float *out, s128 *a, float *b, float t)
{
    if (t >= 1.0f) {
        *(s128 *)out = *a;
    } else {
        __asm__ __volatile__("mfc1 $8, %3\n"
                             "qmtc2 $8, vf07\n"
                             "lqc2 vf05, 0x0(%1)\n"
                             "lqc2 vf06, 0x0(%2)\n"
                             "vsubx.w vf08, vf00, vf07x\n"
                             "vmulax.xyzw ACC, vf05, vf07x\n"
                             "vmaddw.xyzw vf09, vf06, vf08w\n"
                             "sqc2 vf09, 0x0(%0)\n"
                             : : "r"(out), "r"(a), "r"(b), "f"(t) : "$8", "memory");
    }
    out[3] = 1.0f;
}
