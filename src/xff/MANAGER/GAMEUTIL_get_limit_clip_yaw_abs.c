extern int GAMEUTIL_is_between_yaw_and_yaw_extend_abs(float, float, float, float);
extern float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(float, float);
float GAMEUTIL_get_limit_clip_yaw_abs(int *clipped, float yaw, float center, float left, float right)
{
    int changed = 0;
    if (!GAMEUTIL_is_between_yaw_and_yaw_extend_abs(yaw, center, left, right)) {
        float movement = GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(center, yaw);
        yaw = left;
        if (!(0.0f <= movement)) yaw = right;
        changed = 1;
    }
    if (clipped) *clipped = changed;
    return yaw;
}
