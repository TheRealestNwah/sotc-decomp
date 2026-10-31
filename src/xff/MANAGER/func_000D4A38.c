extern void iosFree(void *p);

static void func_000D4A38(void *obj, char *work)
{
    void *p;

    p = *(void **)(*(char **)(work + 0x3E0) + 0x14);
    if (p != 0) {
        iosFree(p);
    }
}
