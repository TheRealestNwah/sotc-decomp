static void func_0004E888(char *p)
{
    char *q = *(char **)(p + 0x50);
    *(float *)(p + 0x28) *= *(float *)(q + 0x70);
    *(float *)(p + 0x24) *= *(float *)(q + 0x74) * *(float *)(q + 0x14);
}
