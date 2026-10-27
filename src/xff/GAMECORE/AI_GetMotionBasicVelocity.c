typedef struct { char pad[0x190]; float delta; } GlobalVar;
extern GlobalVar gcGlobalVar;

void AI_GetMotionBasicVelocity(float *out, float *motion, float time)
{
    float delta = gcGlobalVar.delta;
    float scale;
    if (delta != 0.0f) {
        scale = 1.0f;
        delta = delta * time;
    } else {
        delta = 0.0333667f;
        scale = 1.0f;
        delta = time * delta;
    }
    scale /= delta;
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         ".set reorder\n"
                         : : "r"(out), "r"(motion), "r"(scale) : "memory");
}
