extern void func_00081D08(char *);

void initLwsOriDefSeg(char *s)
{
    int i = *(int *)(s + 0xC);
    char *p = *(char **)(s + 0x10);
    while (--i != -1) {
        func_00081D08(p);
        p += 0x18;
    }
}
