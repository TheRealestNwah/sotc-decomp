extern void _gameFWorkSet(int, float);
void setPlayerMaxGrip(float grip)
{
    float clamped;
    if (700.0f < grip) clamped = 700.0f;
    else if (grip < 100.0f) clamped = 100.0f;
    else clamped = grip;
    _gameFWorkSet(12, clamped);
}
