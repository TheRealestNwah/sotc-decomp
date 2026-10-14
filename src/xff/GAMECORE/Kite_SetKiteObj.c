void Kite_SetKiteObj(char *p, int a1)
{
    *(int *)(p + 0xF0) = a1;
    *(int *)(p + 0x1E8) = a1;
}
