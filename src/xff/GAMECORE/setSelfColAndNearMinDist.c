void setSelfColAndNearMinDist(char *p, int a1, float f1)
{
    *(float *)(p + 0x3C0) = f1;
    *(int *)(p + 0x3C4) = a1;
}
