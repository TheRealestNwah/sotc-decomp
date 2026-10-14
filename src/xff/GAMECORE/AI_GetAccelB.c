float AI_GetAccelB(float x0, float x1, float d, float dt)
{
    float t = (dt < 0.0333667f) ? 0.0333667f : dt;

    return 2.0f * ((x0 - x1) - (x0 - d / t) * 3.0f) / t;
}
