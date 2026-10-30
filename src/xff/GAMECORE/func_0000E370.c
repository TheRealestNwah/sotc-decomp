extern float GAMEUTIL_get_dist_ratio(float, float, float);

static float func_0000E370(int on, int lock, int left, int right, float range, float d, float scale)
{
    if (on == 1 && lock == 0 && (left == 1 || right == 1))
        return GAMEUTIL_get_dist_ratio(d < 0.0f ? -d : d, range, 1.0f) * scale;
    return 0.0f;
}
