extern float B_00054C00[];

float iosGetTableSin(short angle)
{
    int i = (short)(angle - 0x4000);
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
