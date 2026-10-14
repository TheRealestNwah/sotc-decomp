extern int memcmp(const void *, const void *, unsigned int);

int _compPassagePos(char **p)
{
    char *q = p[3];
    if (q == 0)
        goto no;
    if (memcmp(p[0] + 0x10, q, 12) != 0)
        return 1;
no:
    return 0;
}
