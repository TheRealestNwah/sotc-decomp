/* The empty noreorder block stops the assembler from moving the final sqc2
   into the return delay slot, as in the original. */
typedef struct {
    char pad0[0x190];
    float speed;
} GlobalVar;

extern GlobalVar gcGlobalVar;

void AI_GetMotionBasicVelocity(float *out, float *in, float t)
{
    float s = gcGlobalVar.speed;
    float one;
    float scale;

    if (s != 0.0f) {
        one = 1.0f;
        s = s * t;
    } else {
        s = 0.033366699f;
        s = t * s;
        one = 1.0f;
    }
    scale = one / s;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         ".set noreorder\n"
                         ".set reorder\n"
                         : : "r"(out), "r"(in), "r"(scale) : "memory");
}
