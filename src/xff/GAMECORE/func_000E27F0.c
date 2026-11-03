typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) V4;

typedef struct {
    char pad0[0x6C];
    float x6C;
} ViewAngleParam;

typedef struct {
    ViewAngleParam *param;
    char pad4[0xD0 - 0x4];
    float yaw;
} ViewAngleWork;

extern int GAMEUTIL_check_and_get_normalize_vector(float *, int, float *);
extern void GAMEUTIL_get_direction_by_yaw(float *, float);
extern float GAMEUTIL_convert_from_cos_to_linear_ratio(float);
extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern float GAMEUTIL_get_interp_value(float, float, float);

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

static float func_000E27F0(float *vec, ViewAngleWork *w)
{
    V4 n;
    V4 t;
    float r;

    t.x = vec[0];
    t.y = 0.0f;
    t.z = vec[2];
    t.w = 0.0f;
    n = t;
    if (GAMEUTIL_check_and_get_normalize_vector(&n.x, 0, &n.x) == 1) {
        GAMEUTIL_get_direction_by_yaw(&t.x, w->yaw);
        r = GAMEUTIL_convert_from_cos_to_linear_ratio(-vecDot(&n.x, &t.x));
        r = GAMEUTIL_get_dist_ratio(r, 0.4f, 1.0f);
        return GAMEUTIL_get_interp_value(w->param->x6C, 1.0f, r);
    }
    return 1.0f;
}
