extern char gcGlobalVar[];
extern long __muldi3(long, long);

void ChangeGameAnimeTimeScaleRatio(float ratio, float time)
{
    char *g = gcGlobalVar;

    *(float *)(g + 0x1A8) = ratio;
    *(float *)(g + 0x1A4) = time;
    if (time == 0.0f) {
        *(float *)(g + 0x1A0) = ratio;
        *(unsigned long *)(g + 0x160) = *(unsigned long *)(g + 0x148) + *(unsigned long *)(g + 0x160);
        *(unsigned long *)(g + 0x158) = ((*(unsigned long *)g << 8 >> 8) * (int)(ratio * 256.0f)) >> 8;
        *(unsigned long *)(g + 0x148) = 0;
    }
}
