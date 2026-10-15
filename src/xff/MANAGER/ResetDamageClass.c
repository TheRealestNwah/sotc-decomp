void ResetDamageClass(char *d)
{
    *(int *)(d + 0x54) = -1;
    *(int *)(d + 0x58) = 0;
    *(int *)(d + 0x0) = 0;
    *(int *)(d + 0x5C) = 0;
    *(int *)(d + 0x64) = 0;
    *(int *)(d + 0x60) = -1;
    *(int *)(d + 0x68) = 0;
}
