static int func_000B74C0(char *p, int key)
{
    char *node = *(char **)(p + 0x14);
    while (node != 0) {
        if (key == *(int *)(node + 0xC)) {
            return 1;
        }
        node = *(char **)(node + 0x58);
    }
    return 0;
}
