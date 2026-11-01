extern float GAMEUTIL_increase_yaw_limit_extend(int *, float, float);
extern int GAMEUTIL_is_between_yaw_and_yaw(float, float, float);
extern float GAMEUTIL_get_difference_yaw_and_yaw(float, float);

float GAMEUTIL_increase_yaw_limit_clip_extend(int *out, int clipMin, int clipMax, float yaw, float add, float min, float max)
{
    int flag = 0;
    float r;
    float dmin;

    r = GAMEUTIL_increase_yaw_limit_extend(&flag, yaw, add);
    if (!GAMEUTIL_is_between_yaw_and_yaw(r, min, max)) {
        dmin = GAMEUTIL_get_difference_yaw_and_yaw(r, min);
        if (dmin <= GAMEUTIL_get_difference_yaw_and_yaw(r, max)) {
            if (clipMin == 1) {
                flag = clipMin;
                r = min;
            }
        } else if (clipMax == 1) {
            flag = clipMax;
            r = max;
        }
    }
    if (out != 0)
        *out = flag;
    return r;
}
