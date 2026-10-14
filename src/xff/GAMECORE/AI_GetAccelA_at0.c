float AI_GetAccelA_at0(float x0, float x1, float dt)
{
    dt = (dt < 0.0333667f) ? 0.0333667f : dt;
    return (x1 - x0) * -2.0f / (dt * dt);
}
