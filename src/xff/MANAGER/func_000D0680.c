typedef struct Hook {
    void (*fn)(void *);
    struct Hook *next;
} Hook;

extern Hook *B_0014DC68;

static int func_000D0680(void *arg)
{
    Hook *h;

    for (h = B_0014DC68; h != 0; h = h->next)
        h->fn(arg);
    return 1;
}
