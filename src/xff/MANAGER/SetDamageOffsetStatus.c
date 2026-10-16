typedef int s128 __attribute__((mode(TI)));

int SetDamageOffsetStatus(char *d, int type, s128 *ofs, float scale)
{
    *(int *)(d + 0x6C) = type;
    if (ofs != 0) {
        *(s128 *)(d + 0x80) = *ofs;
        *(int *)(d + 0x70) = 1;
    } else {
        *(int *)(d + 0x70) = 0;
    }
    *(float *)(d + 0x90) = scale;
    return 0;
}
