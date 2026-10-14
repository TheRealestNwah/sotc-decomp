void spriteSetScale(char *p, float f1, float f2)
{
    *(float *)(p + 0x40) = f1;
    *(float *)(p + 0x44) = f2;
}
