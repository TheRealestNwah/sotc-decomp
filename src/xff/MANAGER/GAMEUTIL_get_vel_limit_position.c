float GAMEUTIL_get_vel_limit_position(float cur, float target, float speed, float dt)
{
    float d;
    if (0.0f <= speed) {
        d = target - cur;
        speed *= dt;
        if ((d < 0.0f ? -d : d) <= speed)
            return target;
        if (0.0f <= d)
            return cur + speed;
        return cur - speed;
    }
    return target;
}
