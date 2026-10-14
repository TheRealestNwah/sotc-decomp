float GAMEUTIL_get_move_limit_position(float *ratio, float cur, float target, float speed, float dt)
{
    float diff = target - cur;
    float step;

    if (diff < 0.0f) {
        step = speed * dt;
        if (-diff <= step) {
            goto reach;
        }
        goto move;
    }
    step = speed * dt;
    if (diff <= step) {
reach:
        if (ratio != 0) {
            if (dt != 0.0f) {
                speed = diff / dt;
                if (speed < 0.0f) {
                    speed = -speed;
                }
            }
            *ratio = speed;
        }
        return target;
    }
move:
    if (ratio != 0) {
        *ratio = speed;
    }
    if (diff > 0.0f) {
        return cur + step;
    }
    return cur - step;
}
