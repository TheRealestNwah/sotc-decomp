extern int is_emitter_need_disp(char *, int);

static int func_000C5980(char *n)
{
    int r = 0;

    while (n != 0) {
        char *p = n + 0x10;
        int v = is_emitter_need_disp(p, *(int *)(*(char **)n + 0x48));

        *(int *)(p + 0x164) = v;
        if (v == 1)
            r = 1;
        n = (char *)*(int *)(n + 0x1B0);
    }
    return r;
}
