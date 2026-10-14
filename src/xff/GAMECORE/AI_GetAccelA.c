float AI_GetAccelA(float start, float end, float time, float velocity)
{
    float step = time < 0.0333667f ? 0.0333667f : time;

    return (2.0f * ((end - start) - (velocity * step))) / (step * step);
}
