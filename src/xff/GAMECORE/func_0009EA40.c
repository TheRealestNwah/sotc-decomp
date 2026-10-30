extern void iosFree(void *);

static void func_0009EA40(void *unused, char *work)
{
    if (work && *(void **)(work + 0x278))
        iosFree(*(void **)(work + 0x278));
}
