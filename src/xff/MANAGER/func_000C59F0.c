extern int func_000C5BD0(char *, char *, int);

static int func_000C59F0(char *n)
{
    while (n != 0) {
        char *e = *(char **)(*(char **)n + 0x48);

        if (func_000C5BD0(n + 0x10, e, *(int *)(e + 0xD4)) == 1)
            return 1;
        n = *(char **)(n + 0x1B0);
    }
    return 0;
}
