typedef void (*SubFn)(int, void *);
extern char *isysGetThisSubThread(void);
extern void isysSleepSubThread(void);

static void T_000DB4A8(void)
{
    char *th = isysGetThisSubThread();
    char *w = *(unsigned char *)(th + 8) == 0xC ? th + 0x20 : 0;

    for (;;) {
        SubFn fn = *(SubFn *)(w + 0x3F0);
        if (fn)
            fn(*(int *)th, w);
        isysSleepSubThread();
    }
}
