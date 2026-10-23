extern float B_00054C00[];

float iosGetTableCos(short angle)
{
    int i = angle;
    int neg;
    float f;

    i = i < 0 ? -i : i;
    neg = 0;
    if (i >= 0x4000) {
        neg = 1;
        i = 0x8000 - i;
    }
    f = B_00054C00[i];
    if (neg) {
        f = -f;
    }
    return f;
}
