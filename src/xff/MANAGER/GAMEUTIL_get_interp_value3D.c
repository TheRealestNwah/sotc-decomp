typedef int s128 __attribute__((mode(TI)));

void GAMEUTIL_get_interp_value3D(s128 *out, s128 *a, s128 *b, float t)
{
    if (t <= 0.0f) {
        *out = *b;
        return;
    }
    if (t >= 1.0f || (((float *)a)[0] == ((float *)b)[0] && ((float *)a)[1] == ((float *)b)[1] && ((float *)a)[2] == ((float *)b)[2])) {
        *out = *a;
        return;
    }
    __asm__ __volatile__("mfc1 $8, %3\n"
                         "qmtc2 $8, vf07\n"
                         "lqc2 vf05, 0x0(%1)\n"
                         "lqc2 vf06, 0x0(%2)\n"
                         "vsubx.w vf08, vf00, vf07x\n"
                         "vmulax.xyz ACC, vf05, vf07x\n"
                         "vmaddw.xyz vf05, vf06, vf08w\n"
                         "sqc2 vf05, 0x0(%0)\n"
                         ".set noreorder\n.set reorder\n"
                         : : "r"(out), "r"(a), "r"(b), "f"(t) : "$8", "memory");
}
