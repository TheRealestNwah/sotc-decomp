extern void initAnimDefSegOneElement(char *);

void initAnimDefSeg(char *s)
{
    int i = *(int *)(s + 0xC);
    char *p = *(char **)(s + 0x10);
    while (--i != -1) {
        initAnimDefSegOneElement(p);
        p += 0x74;
    }
}
