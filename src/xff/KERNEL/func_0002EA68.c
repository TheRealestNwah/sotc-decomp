static int func_0002EA68(unsigned char *p)
{
    if (p[0] != 'E' || p[1] != 'Q' || p[2] != 'A' || p[3] != 'T')
        return -1;
    return *(int *)(p + 4);
}
