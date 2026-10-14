float getRatioFromInterp(float duration, float time)
{
    float ratio;

    if (duration <= 0.001f) {
        return 1.0f;
    }
    ratio = time / duration;
    if (ratio <= 1.0f) {
        return ratio;
    }
    return 1.0f;
}
