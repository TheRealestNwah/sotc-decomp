typedef int s128 __attribute__((mode(TI)));
extern char *GetLayoutClass(void *);

static int func_000ED2E8(s128 *out, char *p)
{
    char *cls = GetLayoutClass(*(void **)(p + 0x128));
    if (cls == 0) {
        return 0;
    }
    *out = **(s128 **)(cls + 0x134);
    return 1;
}
