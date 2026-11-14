/* Parked: 162 diffs. Weighted random pick over a DLD entry list. Original saves only f20 (remaining weight); share/acc/r stay in caller-saved FPRs, and the walk pointer is a2 with first kept in s2. */
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
    Entry *e;
    float remaining = 100.0f;
    float share;
    float acc;
    float r;
    int count = 0;
    int unset = 0;
    int i;

    for (e = first; dldEntry(&e->ref) != 0; e++) {
        if (e->weight < 0.0f)
            unset++;
        else
            remaining -= e->weight;
        count++;
    }
    acc = 0.0f;
    share = 0.0f;
    r = (float)(rand() & 0xFFFF) * 0.0000152587890625f;
    if (remaining >= 0.0f && unset != 0 && !(remaining < 0.0f))
        share = remaining / (float)unset;
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
