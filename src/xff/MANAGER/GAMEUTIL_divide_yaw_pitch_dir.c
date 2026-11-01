typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

extern s128 ZUnitVector;

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
static inline float vecDot(float *a, float *b)
{
    float dot;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(a), "r"(b) : "$2");
    return dot;
}

static inline int is_divisible(float y)
{
    if (y < 0.0f) {
        if (-0.9999f <= y) {
            goto yes;
        } else {
            goto no;
        }
    } else {
        if (y <= 0.9999f) {
            goto yes;
        } else {
            goto no;
        }
    }
yes:
    return 1;
no:
    return 0;
}

int GAMEUTIL_divide_yaw_pitch_dir(s128 *yaw, Vec4 *pitch, float *dir)
{
    if (is_divisible(dir[1]) == 1) {
        Vec4 t;
        t.q = *(s128 *)dir;
        t.i[1] = 0;
        normalizeXYZ(t.f, t.f);
        if (yaw != 0) {
            *yaw = t.q;
        }
        if (pitch != 0) {
            pitch->i[0] = 0;
            pitch->f[1] = dir[1];
            pitch->f[2] = vecDot(dir, t.f);
            pitch->i[3] = 0;
        }
        return 1;
    }
    if (yaw != 0) {
        *yaw = ZUnitVector;
    }
    if (pitch != 0) {
        pitch->q = ZUnitVector;
    }
    return 0;
}
