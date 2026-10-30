typedef struct Hook {
    char pad0[0xC];
    void (*func)(void *, struct Hook *);
    char pad10[0x20];
    int active;
} Hook;

static void func_000D45D0(void *unused, char *obj)
{
    Hook *hook = *(Hook **)(obj + 0x3E0);
    if (hook->func != 0) {
        hook->func(obj, hook);
    }
    hook->active = 0;
}
