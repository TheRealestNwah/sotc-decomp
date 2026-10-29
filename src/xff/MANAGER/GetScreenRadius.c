typedef float Vector[4] __attribute__((aligned(16)));
static inline void transform(Vector out, void *matrix, Vector v)
{
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
                         : : "r"(matrix), "r"(out), "r"(v)
                         : "memory");
}
static inline float cameraZ(char *camera, Vector position)
{
    Vector unused;
    Vector out;
    transform(out, camera + 0x1A0, position);
    return out[2];
}
#define ABS(x) ((x) < 0.0f ? -(x) : (x))
float GetScreenRadius(char *camera, Vector position, float radius)
{
    float depth = ABS(cameraZ(camera, position));
    Vector out;
    Vector v = {radius, 0.0f, depth, 1.0f};
    transform(out, camera + 0xC0, v);
    return out[0] / out[3] - 2048.0f;
}
