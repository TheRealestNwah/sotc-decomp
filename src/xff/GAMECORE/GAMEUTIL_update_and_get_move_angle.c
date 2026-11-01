extern float GAMEUTIL_get_interp_value_ratio_pow(float, float, float, float);
extern float GAMEUTIL_get_new_velocity(float, float, float, float, float);
extern float GAMEUTIL_get_velocity_by_diff_move(int, float, float, float, float);

float GAMEUTIL_update_and_get_move_angle(float *m, float diff, float rate)
{
    float dist;
    float maxv;
    float v;
    float step;

    dist = diff;
    if (diff < 0.0f) {
        dist = -diff;
    }
    maxv = m[5];
    if (dist < m[3]) {
        maxv = GAMEUTIL_get_interp_value_ratio_pow(maxv, m[6], dist / m[3], m[4]);
    }
    v = GAMEUTIL_get_new_velocity(m[0], m[1], m[2], maxv, rate);
    m[0] = v;
    step = v * rate;
    if (dist <= step) {
        m[0] = GAMEUTIL_get_velocity_by_diff_move(1, v, 0.0f, dist, rate);
        return diff;
    }
    if (diff >= 0.0f) {
        return step;
    }
    return -step;
}
