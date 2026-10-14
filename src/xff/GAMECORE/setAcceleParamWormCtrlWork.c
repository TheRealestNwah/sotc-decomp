void setAcceleParamWormCtrlWork(char *p, float f1, float f2)
{
    *(float *)(p + 0x5C) = f1;
    *(float *)(p + 0x60) = f2;
}
