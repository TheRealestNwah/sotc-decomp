extern float calcAngleTime(float, float, float, float);

static float func_0010FB70(char *a, float x)
{
    return calcAngleTime(x, *(float *)(a + 0xA8), *(float *)(a + 0xA4),
                         *(float *)(**(char ***)(a + 0x1C) + 0x78));
}
