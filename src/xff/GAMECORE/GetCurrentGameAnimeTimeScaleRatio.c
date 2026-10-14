extern char gcGlobalVar[];

float GetCurrentGameAnimeTimeScaleRatio(void)
{
    return *(float *)(gcGlobalVar + 0x1A0);
}
