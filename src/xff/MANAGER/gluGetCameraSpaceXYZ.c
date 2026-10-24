typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern void *get_cur_camera_context(void);
extern Vec4 YUnitVector;

static inline void cross(void *out, void *a, void *b)
{
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0(%1)\n"
                         "lqc2 vf6, 0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void normalize(void *out)
{
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 vf5, 0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0(%0)\n"
                         ".set reorder\n"
                         : : "r"(out) : "memory");
}

void gluGetCameraSpaceXYZ(Vec4 *right, Vec4 *up, Vec4 *forward)
{
    char *context = get_cur_camera_context();

    forward->q = ((Vec4 *)(context + 0x150))->q;
    cross(right, &YUnitVector, forward);
    normalize(right);
    cross(up, forward, right);
}
