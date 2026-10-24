float GetScreenRadiusParticle(void *camera, float z, float x)
{
    float out[4] __attribute__((aligned(16)));
    float v[4] __attribute__((aligned(16))) = { x, 0.0f, z, 1.0f };

    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf8, 0(%2)\n"
                         "lqc2 vf14, 0(%0)\n"
                         "lqc2 vf15, 0x10(%0)\n"
                         "lqc2 vf16, 0x20(%0)\n"
                         "lqc2 vf17, 0x30(%0)\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf17, vf8w\n"
                         "sqc2 vf10, 0(%1)\n"
                         ".set reorder\n"
                         : : "r"((char *)camera + 0xC0), "r"(out), "r"(v)
                         : "memory");
    return out[0] / out[3] - 2048.0f;
}
