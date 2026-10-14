void spriteSetPosition(char *p, float f1, float f2)
{
    *(float *)(p + 0x30) = f1;
    *(float *)(p + 0x34) = f2;
}
