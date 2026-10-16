int AI_CheckNormZero(float *v)
{
    if (v[0] < 0.0f) {
        if (!(-0.0001f < v[0]))
            goto nonzero;
    } else if (!(v[0] < 0.0001f)) {
        goto nonzero;
    }
    if (v[1] < 0.0f) {
        if (!(-0.0001f < v[1]))
            goto nonzero;
    } else if (!(v[1] < 0.0001f)) {
        goto nonzero;
    }
    if (v[2] < 0.0f) {
        if (!(-0.0001f < v[2]))
            goto nonzero;
    } else if (!(v[2] < 0.0001f)) {
        goto nonzero;
    }
    return 0;
nonzero:
    return 1;
}
