static int func_000B7500(char *p)
{
    int n = 0;
    int count = *(int *)(p + 0x10);
    char *node = *(char **)(p + 0x14);
    int i;

    if (count > 0) {
        i = count;
        do {
            if (*(int *)(node + 0x54) != 0) {
                n++;
            }
            node = *(char **)(node + 0x58);
        } while (--i != 0);
    }
    return n;
}
