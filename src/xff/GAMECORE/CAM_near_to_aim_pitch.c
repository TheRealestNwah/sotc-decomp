extern int GAMEUTIL_inc_or_dec_for_near_to_aim_pitch(float *, int, float, float, float, float, float);
static inline void clampPitch(float *output, int direction, float from, float next, float aim)
{
    float value = next;
    if (from == aim || next == aim)
        value = aim;
    else if (direction == 1) {
        if (next > aim)
            value = aim;
    } else if (direction == -1) {
        if (next < aim)
            value = aim;
    }
    if (output)
        *output = value;
}
float CAM_near_to_aim_pitch(int *direction, int clip, float from, float step, float aim, float high, float low)
{
    float result = 0.0f;
    int moved = GAMEUTIL_inc_or_dec_for_near_to_aim_pitch(&result, clip, from, step, aim, high, low);
    clampPitch(&result, moved, from, result, aim);
    if (direction)
        *direction = moved;
    return result;
}
