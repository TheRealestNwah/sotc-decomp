extern float func_0000E158(void *, float);
extern float func_0000E198(float, void *);
extern float GAMEUTIL_get_move_radi_from_pitch1_to_pitch2(float, float);
extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern float powf(float, float);
extern float GAMEUTIL_get_cur_velocity_move_angle(void *);
extern float func_0000E1D8(void *, int, int, int, int, float, float, float, float, float, float, int, float, float, float, float);
extern float update_base_pitch_nico_yaw_pitch_cntrl(void *, float);

static void func_0000CBA0(char *c, float *v, float f)
{
    float pitch = *(float *)(c + 0x68);
    float up = GAMEUTIL_get_move_radi_from_pitch1_to_pitch2(pitch, func_0000E158(c, pitch));
    float dn = GAMEUTIL_get_move_radi_from_pitch1_to_pitch2(pitch, func_0000E198(pitch, c));
    float m = 0.0f, am, r;

    if (up < 0.0f)
        up = 0.0f;
    if (dn > 0.0f)
        dn = 0.0f;
    m = up;
    if (!(m <= -dn))
        m = dn;
    am = m;
    if (m < 0.0f)
        am = -m;
    r = powf(GAMEUTIL_get_dist_ratio(am, 0.0f, *(float *)(c + 0xFC)), *(float *)(c + 0x100));
    *(float *)(c + 0x64) = func_0000E1D8(c + 0x60, *(int *)(c + 0xE8), *(int *)(c + 0x30), *(int *)(c + 0x44), *(int *)(c + 0x48), *(float *)(c + 0x78), f, *(float *)(c + 0x60), v[4], v[5], v[6], *(int *)(c + 0x4C), v[7], GAMEUTIL_get_cur_velocity_move_angle(c + 0xB0), m, r);
    *(float *)(c + 0x64) = update_base_pitch_nico_yaw_pitch_cntrl(c, *(float *)(c + 0x64));
}
