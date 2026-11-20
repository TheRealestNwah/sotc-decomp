extern int GAMEUTIL_check_and_get_normalize_vector(float *, int, float *);
extern float GAMEUTIL_get_dist_ratio(float, float, float);

#define ABS(x) ((x) < 0.0f ? -(x) : (x))

static inline void normInput(float *a, float *b, float x, float y)
{
    float v[4] __attribute__((aligned(16)));
    float m;

    v[0] = x;
    v[1] = y;
    v[2] = 0.0f;
    v[3] = 0.0f;
    if (GAMEUTIL_check_and_get_normalize_vector(v, 0, v) == 1) {
        m = ABS(v[0]);
        if (m < ABS(v[1]))
            m = ABS(v[1]);
        m = 1.0f / m;
        *a = m * x;
        *b = m * y;
        if (ABS(*a) > 1.0f) {
            if (*a >= 0.0f)
                *a = 1.0f;
            else
                *a = -1.0f;
        }
        if (ABS(*b) > 1.0f) {
            if (*b >= 0.0f)
                *b = 1.0f;
            else
                *b = -1.0f;
        }
    } else {
        *a = x;
        *b = y;
    }
}

int is_predict_to_acting_base_yaw_rot_nico_yaw_pitch_cntrl(char *c, float x, float y)
{
    float a, b;
    float r;
    int en, s30, s34, s38;
    float lim, aa;
    normInput(&a, &b, x, y);
    en = *(int *)(c + 0xCC);
    s30 = *(int *)(c + 0x30);
    s34 = *(int *)(c + 0x34);
    s38 = *(int *)(c + 0x38);
    lim = *(float *)(c + 0x70);
    aa = a;
    if (en == 1 && s30 == 0 && (s34 == 1 || s38 == 1))
        r = GAMEUTIL_get_dist_ratio(ABS(aa), lim, 1.0f);
    else
        r = 0.0f;
    return 0.0f < r;
}
