extern void iosFree(void *p);

static void func_000AABE8(void *obj, char *work)
{
    if (work != 0 && *(void **)(work + 0x360) != 0) {
        iosFree(*(void **)(work + 0x360));
    }
}
