typedef struct {
    float x, y, z, w;
} __attribute__((aligned(8))) Vec4;

extern float iosGetACosfExact(float);
extern int GAMEUTIL_is_yaw_pitch_get_direction(float *);

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

int GAMEUTIL_get_yaw_pitch_by_direction(float *yaw, float *pitch, float *dir)
{
    Vec4 v __attribute__((aligned(16)));

    v = (Vec4){dir[0], 0.0f, dir[2], 0.0f};
    normalizeXYZ(&v.x, &v.x);
    {
        float a = iosGetACosfExact(v.z);
        if (v.x < 0.0f) {
            a = -a;
        }
        *yaw = a;
    }
    *pitch = iosGetACosfExact(vecDot(&v.x, dir));
    if (dir[1] < 0.0f) {
        *pitch = -*pitch;
    }
    return GAMEUTIL_is_yaw_pitch_get_direction(dir);
}
