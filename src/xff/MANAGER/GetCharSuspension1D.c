float GetCharSuspension1D(float *vel, float target, float pos, float base,
                          float limit, float damp, float up, float down,
                          float scale, float step, float rate)
{
    float diff = target - pos;
    float r = 1.0f - damp;
    float d30 = diff * 30.0f;
    float t;
    float v = *vel;
    float result;
    float offset;
    if (diff < 0.0f)
        *vel = v + d30 * (damp + up * r);
    else
        *vel = v + d30 * (damp + down * r);
    *vel *= scale;
    result = pos + *vel * step;
    offset = result - base;
    if (offset < 0.0f ? limit < -offset : limit < offset) {
        if (offset < 0.0f) {
            t = -limit;
            result = t + base;
        } else
            result = limit + base;
        *vel = (result - pos) * rate * scale;
    }
    return result;
}
