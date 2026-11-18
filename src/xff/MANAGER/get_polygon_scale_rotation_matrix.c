typedef float Mat[4][4] __attribute__((aligned(16)));

extern float ZUnitVector[4];
extern void iosRotMatrixFromDirection(void *, void *, void *, int);
extern void iosScaleMatrix(void *, float, float, float);

typedef struct {
    char pad0[0x40];
    float dir[4];
    float sx;
    float sy;
    char pad58[0xDC - 0x58];
    int scaled;
    Mat mat;
} Effect;

#define NOTNEAR(d) ((d) < 0.0f ? (d) < -0.099999995f : 0.099999995f < (d))

static inline void matMul(void *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "lqc2 vf24, 0x0(%2)\n"
                         "lqc2 vf25, 0x10(%2)\n"
                         "lqc2 vf26, 0x20(%2)\n"
                         "lqc2 vf27, 0x30(%2)\n"
                         "vmulax.xyzw ACC, vf14, vf24x\n"
                         "vmadday.xyzw ACC, vf15, vf24y\n"
                         "vmaddaz.xyzw ACC, vf16, vf24z\n"
                         "vmaddw.xyzw vf24, vf17, vf24w\n"
                         "vmulax.xyzw ACC, vf14, vf25x\n"
                         "vmadday.xyzw ACC, vf15, vf25y\n"
                         "vmaddaz.xyzw ACC, vf16, vf25z\n"
                         "vmaddw.xyzw vf25, vf17, vf25w\n"
                         "vmulax.xyzw ACC, vf14, vf26x\n"
                         "vmadday.xyzw ACC, vf15, vf26y\n"
                         "vmaddaz.xyzw ACC, vf16, vf26z\n"
                         "vmaddw.xyzw vf26, vf17, vf26w\n"
                         "vmulax.xyzw ACC, vf14, vf27x\n"
                         "vmadday.xyzw ACC, vf15, vf27y\n"
                         "vmaddaz.xyzw ACC, vf16, vf27z\n"
                         "vmaddw.xyzw vf27, vf17, vf27w\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf27, 0x30(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static void get_polygon_scale_rotation_matrix(Effect *e)
{
    Mat s;
    float d;

    iosRotMatrixFromDirection(e->mat, ZUnitVector, e->dir, 0);
    if ((d = e->sx - 1.0f, NOTNEAR(d)) || (d = e->sy - 1.0f, NOTNEAR(d))) {
        e->scaled = 1;
        iosScaleMatrix(s, e->sx, e->sy, 1.0f);
        matMul(e->mat, e->mat, s);
    } else {
        e->scaled = 0;
    }
}
