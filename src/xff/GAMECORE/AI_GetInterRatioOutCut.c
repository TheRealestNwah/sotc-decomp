float AI_GetInterRatioOutCut(float value, float low, float high, float start, float end)
{
    float span;
    float result;

    if (value <= low) {
        result = start;
        goto done;
    }
    if (high <= value) {
        result = end;
        goto done;
    }
    span = high - low;
    if (span == 0.0f) {
        result = start;
        goto done;
    }
    return (((value - low) * (end - start)) / span) + start;

done:
    return result;
}
