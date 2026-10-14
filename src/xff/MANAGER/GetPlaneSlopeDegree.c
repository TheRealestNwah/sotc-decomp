extern float iosGetACosfExact(float);

float GetPlaneSlopeDegree(float *normal)
{
    float y = normal[1];

    if (y >= 1.0f) {
        return 0.0f;
    }
    if (y <= -1.0f) {
        return 180.0f;
    }
    return iosGetACosfExact(y) * 57.29578f;
}
