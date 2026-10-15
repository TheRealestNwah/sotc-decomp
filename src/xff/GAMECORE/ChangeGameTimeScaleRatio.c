extern char gcGlobalVar[];

extern int func_0000BB50();

int ChangeGameTimeScaleRatio(float ratio)
{
    char *g = gcGlobalVar;

    *(float *)(g + 0x19C) = ratio;
    return func_0000BB50();
}
