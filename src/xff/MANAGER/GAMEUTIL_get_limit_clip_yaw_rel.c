extern float func_00007948(float);
extern float GAMEUTIL_get_limit_clip_yaw_abs(int *, float, float, float, float);

static inline int is_nearly_zero(float x, float eps)
{
    if (x < 0.0f) {
        if (-x <= eps) {
            goto yes;
        } else {
            goto no;
        }
    } else {
        if (x <= eps) {
            goto yes;
        } else {
            goto no;
        }
    }
yes:
    return 1;
no:
    return 0;
}

float GAMEUTIL_get_limit_clip_yaw_rel(int *clipped, float yaw, float center, float left, float right)
{
    float l = center;
    float r;

    if (is_nearly_zero(left, 0.0001f) == 0)
        l = func_00007948(center + left);
    r = center;
    if (is_nearly_zero(right, 0.0001f) == 0)
        r = func_00007948(center + right);
    return GAMEUTIL_get_limit_clip_yaw_abs(clipped, yaw, center, l, r);
}
