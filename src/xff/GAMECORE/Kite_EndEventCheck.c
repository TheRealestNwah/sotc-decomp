void Kite_EndEventCheck(char *p)
{
    *(int *)(p + 0x4) = 1;
    *(int *)(p + 0xC) = 1;
}
