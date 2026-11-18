extern float func_0000E010(void *, float);
extern float func_0000E0B8(void *, float);
extern float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(float, float);
extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern float powf(float, float);
extern float GAMEUTIL_get_cur_velocity_move_angle(void *);
extern float func_0000E1D8(void *, int, int, int, int, float, float, float, float, float, float, int, float, float, float, float);
extern float update_base_yaw_nico_yaw_pitch_cntrl(void *, float);

static inline int isCcw(float d)
{
    if (0.0f <= d)
        return 1;
    return 0;
}

static void func_0000C9E8(char *c, float f, float *v)
{
    float m = 0.0f, am;
    float r = 1.0f;
    float yaw = *(float *)(c + 0x5C);
    int lim;

    if (*(int *)(c + 0x108) == 1 || *(int *)(c + 0x10C) == 1)
        lim = 1;
    else
        lim = 0;
    if (lim == 1) {
        if (isCcw(GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(*(float *)(c + 0x110), yaw)) == 1) {
            if (*(int *)(c + 0x108) == 1) {
                m = GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(yaw, func_0000E010(c, yaw));
                if (m < 0.0f)
                    m = 0.0f;
            }
        } else if (*(int *)(c + 0x10C) == 1) {
            m = GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(yaw, func_0000E0B8(c, yaw));
            if (0.0f < m)
                m = 0.0f;
        }
        if (m != 0.0f) {
            am = m;
            if (m < 0.0f)
                am = -m;
            r = powf(GAMEUTIL_get_dist_ratio(am, 0.0f, *(float *)(c + 0xE0)), *(float *)(c + 0xE4));
        }
    }
    *(float *)(c + 0x58) = func_0000E1D8(c + 0x54, *(int *)(c + 0xCC), *(int *)(c + 0x30), *(int *)(c + 0x34), *(int *)(c + 0x38), *(float *)(c + 0x70), f, *(float *)(c + 0x54), v[0], v[1], v[2], *(int *)(c + 0x3C), v[3], GAMEUTIL_get_cur_velocity_move_angle(c + 0x88), m, r);
    *(float *)(c + 0x58) = update_base_yaw_nico_yaw_pitch_cntrl(c, *(float *)(c + 0x58));
}

