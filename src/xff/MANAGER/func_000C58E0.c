extern char RO_0011A908[];
extern void *malloc_from_src_partition(void *, int, char *, int);
extern void func_000C5A50(char *, int, int, int, int, int);

static char *func_000C58E0(void *ptn, char *def, int a2, int a3, int t0, int t1)
{
    char *node = malloc_from_src_partition(ptn, 0x1C0, RO_0011A908, 1);

    if (node != 0) {
        *(char **)node = def;
        func_000C5A50(node + 0x10, a2, a3, t0, t1, *(int *)(def + 0x48));
        *(char **)(node + 0x1B0) = 0;
    }
    return node;
}
