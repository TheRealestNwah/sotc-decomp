extern void iosFree(void *p);

static void *func_0000A2C0(char *p)
{
    char *e;
    int n;

    if (p != 0) {
        n = *(int *)(p + 0x40) - 2;
        e = *(char **)(p + 0x30) + 0x20;
        while (n != -1) {
            if (*(int *)(e + 0x18) != 0) {
                *(int *)(e + 0x18) = 0;
                iosFree(*(void **)e);
            }
            n--;
            e += 0x20;
        }
        iosFree(p);
    }
    return p;
}
