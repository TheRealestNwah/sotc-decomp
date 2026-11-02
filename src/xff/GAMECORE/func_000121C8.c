extern void iosFree(void *);

static void func_000121C8(void *unused, char *w)
{
    void (*cb)(void) = *(void (**)(void))(w + 0x2C);

    if (cb != 0) {
        cb();
    }
    --**(int **)(w + 0x30);
    iosFree(w);
}
