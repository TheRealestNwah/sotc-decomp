float AI_GetAccelA_at0(float start, float end, float time)
{
    float step = time < 0.0333667f ? 0.0333667f : time;

    return ((end - start) * -2.0f) / (step * step);
}
