float getTurnLimitInterp(float from, float to, float time, float elapsed)
{
    float t;

    if (time <= 0.001f) {
        return to;
    }
    t = elapsed / time;
    t = (t <= 1.0f) ? t : 1.0f;
    return to * t + from * (1.0f - t);
}
