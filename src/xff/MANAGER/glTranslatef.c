typedef struct { float m[4][4]; } Matrix;
extern int B_001482A0;
extern Matrix B_00147AA0[];
static inline void apply(float *d, Matrix *m, float *v)
{
    __asm__ __volatile__(".set noreorder\n"
        "lqc2 vf8, 0(%2)\n" "lqc2 vf14, 0x0(%0)\n" "lqc2 vf15, 0x10(%0)\n" "lqc2 vf16, 0x20(%0)\n" "lqc2 vf17, 0x30(%0)\n"
        "vmulax.xyzw ACC, vf14, vf8x\n" "vmadday.xyzw ACC, vf15, vf8y\n" "vmaddaz.xyzw ACC, vf16, vf8z\n" "vmaddw.xyzw vf10, vf17, vf8w\n"
        "sqc2 vf10, 0x0(%1)\n" ".set reorder\n" : : "r"(m), "r"(d), "r"(v) : "memory");
}
void glTranslatef(float x, float y, float z) { float v[4] __attribute__((aligned(16))) = {x, y, z, 1.0f}; apply(B_00147AA0[B_001482A0].m[3], &B_00147AA0[B_001482A0], v); }
