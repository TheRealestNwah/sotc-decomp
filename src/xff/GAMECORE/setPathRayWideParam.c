void setPathRayWideParam(char *p, int a1, float f1)
{
    *(float *)(p + 0x3C3C) = f1;
    *(int *)(p + 0x3C40) = a1;
}
