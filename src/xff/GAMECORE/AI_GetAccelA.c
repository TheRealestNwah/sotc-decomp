float AI_GetAccelA(float x0, float x1, float dt, float v0)
{
    float t = (dt < 0.0333667f) ? 0.0333667f : dt;

    return 2.0f * ((x1 - x0) - v0 * t) / (t * t);
}
