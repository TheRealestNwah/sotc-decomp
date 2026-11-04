extern int func_000C5BD0(void *, char *, int);

static int func_000C59F0(char *p)
{
    while (p) {
        char *a = *(char **)(*(char **)p + 0x48);
        if (func_000C5BD0(p + 0x10, a, *(int *)(a + 0xD4)) == 1)
            return 1;
        p = *(char **)(p + 0x1B0);
    }
    return 0;
}
