extern char gcGlobalVar[];
extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern float GAMEUTIL_update_and_get_move_angle(void *, float, float);

static float func_0000DEC0(int *direction, void *move, float near, float far, float value, float current, float center,
                           float max, float min)
{
    float ratio = GAMEUTIL_get_dist_ratio(value < 0 ? -value : value, near, far);
    float target;
    float diff;

    if (value >= 0) {
        if (max <= center)
            target = max;
        else
            target = center + ratio * (max - center);
    } else {
        if (center <= min)
            target = min;
        else
            target = center + ratio * (min - center);
    }
    diff = target - current;
    if (diff < 0 ? -0.0017453292f < diff : diff < 0.0017453292f)
        *direction = 0;
    else if (0 < diff)
        *direction = 1;
    else
        *direction = -1;
    return current + GAMEUTIL_update_and_get_move_angle(move, diff, *(float *)(gcGlobalVar + 0x180));
}
