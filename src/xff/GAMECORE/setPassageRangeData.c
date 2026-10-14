void setPassageRangeData(char *p, float f1, float f2)
{
    *(float *)(p + 0x3CC) = f1;
    *(float *)(p + 0x3D0) = f2;
}
