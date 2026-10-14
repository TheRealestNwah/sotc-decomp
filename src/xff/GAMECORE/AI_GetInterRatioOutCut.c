float AI_GetInterRatioOutCut(float x, float x0, float x1, float y0, float y1)
{
    if (x <= x0) {
        return y0;
    }
    if (x1 <= x) {
        return y1;
    }
    x1 -= x0;
    return (x1 == 0.0f) ? y0 : (x - x0) * (y1 - y0) / x1 + y0;
}
