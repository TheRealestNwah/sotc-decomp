typedef struct Hook {
    char pad0[0x14];
    void (*func)(void *, struct Hook *);
    char pad18[8];
    int state;
    char pad24[4];
    int active;
} Hook;

static void func_000D4468(void *unused, char *obj)
{
    Hook *hook = *(Hook **)(obj + 0x3E0);
    hook->state = 0;
    if (hook->func != 0) {
        hook->func(obj, hook);
    }
    hook->active = 0;
}
