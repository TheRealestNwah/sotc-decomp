extern int D_00179AD8;
extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern float GAMEUTIL_get_interp_value(float, float, float);

float GAMEUTIL_get_sight_on_angle_vel_ratio_float(void)
{
    int v = D_00179AD8;
    float r;

    if (v == 8)
        return 1.0f;
    if (v < 8)
        r = GAMEUTIL_get_interp_value(1.0f, 0.5f, GAMEUTIL_get_dist_ratio(v, 0.0f, 8.0f));
    else
        r = GAMEUTIL_get_interp_value(2.0f, 1.0f, GAMEUTIL_get_dist_ratio(v, 8.0f, 15.0f));
    return r;
}
