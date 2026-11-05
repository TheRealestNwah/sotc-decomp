static inline int isNearZero(float x, float eps)
{
    if (((x < 0.0f) ? -x : x) <= eps)
        return 1;
    return 0;
}

static float func_00007A48(float a, float b, float x)
{
    if (isNearZero(x, 0.0001f))
        return b;
    return a;
}
