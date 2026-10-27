extern float iosGetACosfExact(float);
static inline float lengthSquared(const float *input)
{
    float length;
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf7, 0x0(%1)\n"
        "vmul.xyz vf7, vf7, vf7\n"
        "vaddy.x vf7, vf7, vf7y\n"
        "vaddz.x vf7, vf7, vf7z\n"
        "qmfc2.ni %0, vf7\n"
        ".set reorder\n"
        : "=r"(length) : "r"(input) : "memory");
    return length;
}
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
int GetRootRotStatus(float *output, float *quaternion, float scale)
{
    float angle = iosGetACosfExact(quaternion[3]);
    angle = (angle + angle) * scale;
    output[4] = angle;
    if (lengthSquared(quaternion) != 0.0f && angle != 0.0f) {
        normalizeXYZ(output, quaternion);
        output[3] = 0.0f;
        return 1;
    }
    return 0;
}
