void setUserPathGroupID(char *p, int a1, int a2)
{
    *(int *)(p + 0x3C68) = a1;
    *(int *)(p + 0x3C6C) = a2;
}
