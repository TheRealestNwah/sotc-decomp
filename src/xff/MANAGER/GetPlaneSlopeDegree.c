extern float iosGetACosfExact(float);

float GetPlaneSlopeDegree(const float *plane)
{
    float value = plane[1];

    if (value >= 1.0f) return 0.0f;
    if (value <= -1.0f) return 180.0f;
    return iosGetACosfExact(value) * 57.295777f;
}