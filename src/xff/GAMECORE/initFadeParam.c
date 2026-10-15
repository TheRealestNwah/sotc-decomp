extern char gcGlobalVar[];

void initFadeParam(float *fade, float time)
{
    char *g = gcGlobalVar;

    fade[0] = *(float *)(g + 0x168);
    fade[1] = *(float *)(g + 0x168);
    fade[2] = time;
    fade[4] = time;
    fade[3] = time;
}
