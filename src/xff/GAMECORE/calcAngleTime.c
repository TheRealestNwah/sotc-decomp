extern float calcMoveAngle(float, float *, float, float, float);

static inline int isAngleReached(float angle, float r)
{
    if (__builtin_fabsf(r + angle) <= 0.017453293f)
        return 1;
    if ((angle >= 0.0f && r >= 0.0f) || (angle <= 0.0f && r <= 0.0f))
        return __builtin_fabsf(r) >= __builtin_fabsf(angle);
    return 0;
}

float calcAngleTime(float angle, float x, float speed, float y)
{
    float t;
    float r;

    if (angle >= 0.0f)
        r = calcMoveAngle(speed, &t, x, y, angle);
    else
        r = calcMoveAngle(-speed, &t, x, y, angle);
    if (isAngleReached(angle, r))
        return t;
    t += __builtin_fabsf(r + angle) / speed;
    return t;
}
