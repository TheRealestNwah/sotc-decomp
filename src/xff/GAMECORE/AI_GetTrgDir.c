typedef int Quadword __attribute__((mode(TI)));
static inline void normalizeXYZ(float *output, const float *input)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf5, 0x0(%1)\n"
        "vmul.xyz vf7, vf5, vf5\n"
        "vmulax.w ACC, vf0, vf7x\n"
        "vmadday.w ACC, vf0, vf7y\n"
        "vmaddz.w vf7, vf0, vf7z\n"
        "vrsqrt Q, vf0w, vf7w\n"
        "vwaitq\n"
        "vmulq.xyz vf5, vf5, Q\n"
        "sqc2 vf5, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(output), "r"(input) : "memory");
}
void AI_GetTrgDir(float *output, float *state, float time)
{
    if (state[0x44 / 4] != 0.0f) {
        output[0] = state[0x20 / 4] * state[0x40 / 4];
        output[1] = -(state[0x48 / 4] + time * state[0x48 / 4] / state[0x44 / 4]);
        output[2] = state[0x28 / 4] * state[0x40 / 4];
        output[3] = 0.0f;
        normalizeXYZ(output, output);
    } else {
        *(Quadword *)output = *(Quadword *)(state + 0x20 / 4);
    }
}
