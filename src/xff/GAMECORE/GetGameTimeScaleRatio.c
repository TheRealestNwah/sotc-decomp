extern char gcGlobalVar[];

float GetGameTimeScaleRatio(void)
{
    return *(float *)(gcGlobalVar + 0x19C);
}
