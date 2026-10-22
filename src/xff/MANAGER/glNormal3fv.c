typedef struct {
    float m[16];
} Matrix;

typedef struct {
    char pad0[0x80];
    float normal[4];
    char pad90[0x120];
    unsigned long flags;
} GlState;

extern float D_00130500[4];
extern int B_001482A0;
extern Matrix B_00147AA0[];
extern void iosApplyRotMatrix(void *, void *, void *);

typedef struct {
    float x, y, z, w;
} Vector __attribute__((aligned(16)));

void glNormal3fv(float *values)
{
    float *destination = D_00130500;
    Vector normal = { values[0], values[1], values[2], 0.0f };

    iosApplyRotMatrix(destination, &B_00147AA0[B_001482A0], &normal);
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
                         : : "r"(destination) : "memory");
    ((GlState *)((char *)destination - 0x80))->flags |= 1;
}




