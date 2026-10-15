typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

/* The empty noreorder block stops the assembler from moving the final sqc2
   into the return delay slot, as in the original. */
void iosGetStabYZVector(Vec4 *out, Vec4 *in)
{
    out->q = in->q;
    out->f[0] = 0.0f;
    __asm__ __volatile__("lqc2 vf05, 0(%0)\n"
                         "vmul.xyz vf07, vf05, vf05\n"
                         "vmulax.w ACC, vf00, vf07x\n"
                         "vmadday.w ACC, vf00, vf07y\n"
                         "vmaddz.w vf07, vf00, vf07z\n"
                         "vrsqrt Q, vf00w, vf07w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf05, vf05, Q\n"
                         "sqc2 vf05, 0(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(out) : "memory");
}
