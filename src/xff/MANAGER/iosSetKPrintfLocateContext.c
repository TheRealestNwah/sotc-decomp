void iosSetKPrintfLocateContext(char *p, float f1, float f2)
{
    *(float *)(p + 0x8) = f1;
    *(float *)(p + 0x0) = f1;
    *(float *)(p + 0xC) = f2;
    *(float *)(p + 0x4) = f2;
}
