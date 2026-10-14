char *getInterestPointData(unsigned int *p, int i)
{
    char *r;
    if (p == 0)
        goto no;
    if (i < 0)
        goto no;
    r = (char *)p + i * 32 + 0x10;
    if ((unsigned int)i < p[0])
        return r;
no:
    return 0;
}
