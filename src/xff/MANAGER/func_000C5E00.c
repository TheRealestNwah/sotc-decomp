extern int func_000C5DF0(char *);

static int func_000C5E00(char *p)
{
    if (func_000C5DF0(p) == 1 && *(int *)(p + 0xC0) == 2)
        return 1;
    return 0;
}
