int GAMEUTIL_is_diff_nearly_equal_zero(float value, float other, float tolerance)
{
    value -= other;
    if (value < 0.0f) {
        if (-value <= tolerance) {
            goto nearZero;
        } else {
            goto notNearZero;
        }
    } else {
        if (value <= tolerance) {
            goto nearZero;
        } else {
            goto notNearZero;
        }
    }

nearZero:
    return 1;
notNearZero:
    return 0;
}
