int GAMEUTIL_is_nearly_equal_zero3D(float *value, float tolerance)
{
    if (value[0] < 0.0f) {
        if (-value[0] <= tolerance) {
            goto checkY;
        } else {
            goto notNearZero;
        }
    } else {
        if (value[0] <= tolerance) {
            goto checkY;
        } else {
            goto notNearZero;
        }
    }

checkY:
    if (value[1] < 0.0f) {
        if (-value[1] <= tolerance) {
            goto checkZ;
        } else {
            goto notNearZero;
        }
    } else {
        if (value[1] <= tolerance) {
            goto checkZ;
        } else {
            goto notNearZero;
        }
    }

checkZ:
    if (value[2] < 0.0f) {
        if (-value[2] <= tolerance) {
            goto nearZero;
        } else {
            goto notNearZero;
        }
    } else {
        if (value[2] <= tolerance) {
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
