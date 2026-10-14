void Init_TimeFloatSpeed(char *p, float f1, float f2, float f3)
{
    *(float *)(p + 0x4) = f1;
    *(float *)(p + 0x0) = f2;
    *(float *)(p + 0x8) = f2;
    *(float *)(p + 0xC) = f3;
}
