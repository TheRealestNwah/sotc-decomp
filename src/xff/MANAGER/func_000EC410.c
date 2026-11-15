/* Parked: 14 diffs, same size (167 words) (162 before). Fixes: rand() is evaluated before acc/share are initialised (they no longer live across the call, so only f20 is saved), the first walk uses its own pointer `p` (so `e` can share s0 with `unset`), and an empty memory asm keeps `e = first` out of the beqz delay slot. Remaining: ordering of the walk-pointer/count/unset initialisation moves at 0x94, and the e = first move placement after blez. */
#ifdef NONMATCHING
extern int DldSysUndefSymbol;
extern unsigned char RO_00141E70[];
extern void iosJumpRecoverPoint(void *, ...);
extern int rand(void);
extern void func_000ED618(void *, void *);

typedef struct {
    unsigned int ref;
    float weight;
} Entry;

static inline char *dldEntry(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;

    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != (char *)DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}

static void func_000EC410(unsigned int *list, void *ctx)
{
    Entry *first = (Entry *)dldEntry(list);
    Entry *p;
    Entry *e;
    float remaining = 100.0f;
    float share;
    float acc;
    float r;
    int count = 0;
    int unset = 0;
    int i;

    for (p = first; dldEntry(&p->ref) != 0; p++) {
        if (p->weight < 0.0f)
            unset++;
        else
            remaining -= p->weight;
        count++;
    }
    r = (float)(rand() & 0xFFFF) * 0.0000152587890625f;
    acc = 0.0f;
    share = 0.0f;
    if (remaining >= 0.0f && unset != 0 && !(remaining < 0.0f))
        share = remaining / (float)unset;
    __asm__ volatile("" ::: "memory");
    e = first;
    for (i = 0; i < count; i++, e++) {
        float w = share;
        if (!(e->weight < 0.0f))
            w = e->weight;
        acc += w * 0.01f;
        if (r < acc) {
            if (dldEntry(&e->ref) == (char *)first)
                iosJumpRecoverPoint(RO_00141E70);
            func_000ED618(e, ctx);
            return;
        }
    }
    func_000ED618(first, ctx);
}
#endif
