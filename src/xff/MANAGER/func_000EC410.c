/* Parked: 3 diffs, same size (161 words) (was 9). p, count and unset are
 * initialised as statements before the first walk and the walk advances p
 * before count, which fixes the init move order. rand() is evaluated before
 * acc/share are initialised and the first walk uses its own pointer `p`.
 * Indexing the second walk as &first[i] makes e a strength-reduced giv, so
 * i = 0 fills the blez delay slot like the Original.
 * Remaining: the giv init `e = first` lands after the two hoisted lui
 * (dldEntry's symbols) instead of before them; first + i, char-offset,
 * late-assign and reversed-compare spellings stayed at 3. */
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
    int count;
    int unset;
    int i;

    p = first;
    count = 0;
    unset = 0;
    for (; dldEntry(&p->ref) != 0;) {
        if (p->weight < 0.0f)
            unset++;
        else
            remaining -= p->weight;
        p++;
        count++;
    }
    r = (float)(rand() & 0xFFFF) * 0.0000152587890625f;
    acc = 0.0f;
    share = 0.0f;
    if (remaining >= 0.0f && unset != 0 && !(remaining < 0.0f))
        share = remaining / (float)unset;
    for (i = 0; i < count; i++) {
        float w = share;
        e = &first[i];
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
