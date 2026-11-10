typedef struct { int name; int value; int size; unsigned char info; unsigned char other; unsigned short shndx; } Sym;
typedef struct Link {
    int name;
    Sym *sym;
    unsigned int prev;
    struct Link *next;
} Link;
typedef struct { int key; Link *head; int *data; } HEnt;
typedef struct { char pad0[0x1C]; int count; int *idx; char pad24[4]; Sym *syms; } SymTab;
typedef struct { char pad0[0x1C]; SymTab *tab; char pad20[8]; Link *links; } Module;

extern char B_00054398[];
extern HEnt *SearchStrHashKey(void *, int);
extern int DldSysUndefSymbol;

static inline HEnt *lookup(int name, int *v)
{
    HEnt *h = SearchStrHashKey(B_00054398, name);
    if (h != 0)
        *v = h->data[1];
    return h;
}

static inline void unlinkSym(Link *l)
{
    unsigned int p = l->prev;
    if (p != 0) {
        Link *nx = l->next;
        Sym *ls;
        if (p & 0x80000000)
            ((HEnt *)(p & 0x7FFFFFFF))->head = nx;
        else
            ((Link *)p)->next = nx;
        if (nx != 0)
            nx->prev = p;
        ls = l->sym;
        *(volatile int *)&l->next = 0;
        *(volatile int *)&l->prev = 0;
        ls->other = 1;
        ls->value = DldSysUndefSymbol;
    }
}

static int func_00007E00(Module *m)
{
    SymTab *t = m->tab;
    int n = t->count;
    int found = 0;
    Sym *syms;
    Link *l;
    int *idx;
    int value;

    if (n == 0)
        goto end;
    idx = t->idx;
    syms = t->syms;
    l = m->links;
    while (n--) {
        Sym *s = &syms[*idx];
        if (s->value == DldSysUndefSymbol) {
            HEnt *h = lookup(l->name, &value);
            if (h != 0) {
                unlinkSym(l);
                {
                    Link *hd = h->head;
                    l->prev = (unsigned int)h | 0x80000000;
                    l->next = hd;
                    h->head = l;
                    if (hd != 0)
                        hd->prev = (unsigned int)l;
                }
                s->other = 1;
                s->value = value;
            }
            if (s->other)
                found++;
        }
        idx++;
        l++;
    }
end:
    return found;
}
