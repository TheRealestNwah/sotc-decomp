static void func_000CB9E0(char *p)
{
    void (*cb)(int);
    if (*(int *)(p + 0xF0) == 1) {
        cb = *(void (**)(int))(p + 0xF4);
        if (cb != 0) {
            cb(*(int *)(p + 0xF8));
        }
    }
    *(int *)(p + 0xF4) = 0;
    *(int *)(p + 0xF8) = 0;
}
