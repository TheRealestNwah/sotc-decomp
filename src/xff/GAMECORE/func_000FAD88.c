extern int ClipCollisionDirectCallBackOneObj(void *out, void *a, void *b, void *obj, int, int, int, int);

static int func_000FAD88(char *p, void *a, void *b)
{
    char buf[0x50];
    void *obj = *(void **)(p + 0x3C4);
    if (obj != 0) {
        return ClipCollisionDirectCallBackOneObj(buf, a, b, obj, 0, 0, 0, 0);
    }
    return 0;
}
