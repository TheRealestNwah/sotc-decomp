extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);

static int func_000E32B0(char *p)
{
    int found = 0;

    if (*(void **)(p + 0x1C) != 0) {
        void **it;
        void *obj = 0;

        for (it = isysGroupForFirst(*(void **)(p + 0x8), 0); it != 0; it = isysGroupForNext(it, 0)) {
            obj = *it;
            if (*(void **)(p + 0x1C) == obj) {
                found = 1;
                break;
            }
        }
        if (obj != 0)
            isysGroupForExit(obj, 0);
    }
    return found;
}
