extern int chkNearStickArrow(int, int, float *, float);

int AI_CheckNearArrow(int a, int b, float *c)
{
    return chkNearStickArrow(a, b, c, c[1]);
}
