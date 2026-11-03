extern char *GetScrLwsOriClass(void *);

static int func_00064340(void *a, char *b)
{
    char *ori;
    int *p;
    int n;
    int i;
    int j;

    if (a == *(void **)(b + 0x40)) {
    found:
        return 0;
    }
    ori = GetScrLwsOriClass(a);
    if (ori != 0) {
        n = *(int *)(*(char **)(ori + 0x11F8) + 0x30);
        p = *(int **)(ori + 0x1200);
        for (i = 0; i < n; i++, p += 0x14) {
            if (*p == *(int *)(b + 0x40))
                goto found;
        }
    } else {
        ori = GetScrLwsOriClass(*(void **)(b + 0x40));
        if (ori == 0)
            return 1;
        n = *(int *)(*(char **)(ori + 0x11F8) + 0x30);
        p = *(int **)(ori + 0x1200);
        for (j = 0; j < n; j++, p += 0x14) {
            if (*p == (int)a)
                goto found;
        }
    }
    return 1;
}
