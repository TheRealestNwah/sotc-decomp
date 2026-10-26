extern void RelocateCollisionWork(void *work, void *data);

void func_000AE838(char *layout, void *work)
{
    char *resource = *(char **)(layout + 0x184);

    RelocateCollisionWork(work, *(void **)(resource + 0x20));
}
