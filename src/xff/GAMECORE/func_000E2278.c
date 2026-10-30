static float func_000E2278(float a, float b, float min)
{
    float r;
    if (b < 0.0f) {
        r = -b / a;
    } else {
        r = b / a;
    }
    if (r < min) {
        r = min;
    }
    return r;
}
