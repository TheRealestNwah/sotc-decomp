static inline int isNearZero(float x, float eps)
{
    if (((x < 0.0f) ? -x : x) <= eps)
        return 1;
    return 0;
}

static float func_000079E8(float x)
{
    if (isNearZero(x, 0.0001f))
        return 1.0f;
    return x;
}
