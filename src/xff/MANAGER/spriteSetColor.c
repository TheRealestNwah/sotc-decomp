void spriteSetColor(char *p, int a1, int a2, int a3, int a4)
{
    *(char *)(p + 0x4) = a1;
    *(char *)(p + 0x5) = a2;
    *(char *)(p + 0x6) = a3;
    *(char *)(p + 0x7) = a4;
}
