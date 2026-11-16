static inline int isSideUp(char *w)
{
    float y = *(float *)(w + 0x1F4);
    if (y < 0.0f ? y <= -0.70710677f : 0.70710677f <= y)
        return 1;
    return 0;
}

static inline int isNeg(char *w, char *o)
{
    int r;
    if (*(int *)(w + 0x244) != 0) {
        if (isSideUp(w))
            r = *(float *)(w + 0x1C4) < 0.0f;
        else
            r = 0;
    } else
        r = *(float *)(o + 0x48) + *(float *)(w + 0x34) <= 0.0f;
    return r;
}

static inline int isPos(char *w, char *o)
{
    int r;
    if (*(int *)(w + 0x244) != 0) {
        if (isSideUp(w))
            r = 0.0f < *(float *)(w + 0x1C4);
        else
            r = 0;
    } else
        r = 0.0f <= *(float *)(o + 0x48) - *(float *)(w + 0x34);
    return r;
}

static int func_000B7B08(char *w, char *o)
{
    if (isNeg(w, o) || isPos(w, o))
        return 1;
    return 0;
}
