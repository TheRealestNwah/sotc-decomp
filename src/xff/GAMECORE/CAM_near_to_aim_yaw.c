extern int GAMEUTIL_inc_or_dec_for_near_to_aim_yaw(float *, float, float, float);
static inline void clampYaw(float *output, int direction, float from, float next, float aim, float step)
{
    float value = next;
    if (from == aim || next == aim)
        value = aim;
    else if (direction == 1) {
        float bound = aim;
        if (aim < from)
            bound = aim + 6.2831852f;
        if (from + step > bound)
            value = aim;
    } else if (direction == -1) {
        float bound = aim;
        if (from < aim)
            bound = aim - 6.2831852f;
        if (from - step < bound)
            value = aim;
    }
    if (output)
        *output = value;
}
float CAM_near_to_aim_yaw(int *direction, float from, float step, float aim)
{
    float result = 0.0f;
    int moved = GAMEUTIL_inc_or_dec_for_near_to_aim_yaw(&result, from, step, aim);
    clampYaw(&result, moved, from, result, aim, step);
    if (direction)
        *direction = moved;
    return result;
}
