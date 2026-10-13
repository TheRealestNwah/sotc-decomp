int GAMEUTIL_is_nearly_equal_zero(float value, float tolerance)
{
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
