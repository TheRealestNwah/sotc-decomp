void iosSetKPrintfColorContext(char *p, int c, float r, float g, float b, float a)
{
    *(float *)(p + 0x20) = r;
    *(float *)(p + 0x24) = g;
    *(float *)(p + 0x28) = b;
    *(float *)(p + 0x2C) = a;
    *(int *)(p + 0x30) = c;
}
