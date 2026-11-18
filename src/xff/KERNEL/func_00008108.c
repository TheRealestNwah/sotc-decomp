typedef struct { int name; int value; int size; unsigned char info; unsigned char other; unsigned short shndx; } Sym;
typedef struct Link {
    int name;
    Sym *sym;
    unsigned int prev;
    struct Link *next;
} Link;
typedef struct { int key; Link *head; int used; int x0C; } Exp;
typedef struct { char pad0[0x1C]; int count; } SymTab;
typedef struct { char pad0[0x1C]; SymTab *tab; char pad20[4]; Exp *exps; Link *links; int flags; } Module;

extern char B_00054398[];
extern int DldSysUndefSymbol;
extern void DeleteStrHashKey(void *, void *);
extern void iosFree(void *);

static void func_00008108(Module *m)
{
    int n;
    int n2;
    Exp *e;
    Link *l;

    int f = m->flags;

    if (f < 0) {
        e = m->exps;
        if (e != 0) {
            n = f & 0x1FFFFFFF;
            while (n--) {
                if (e->used) {
                    Link *l2 = e->head;
                    e->head = 0;
                    while (l2 != 0) {
                        Link *nx = l2->next;
                        Sym *s = l2->sym;
                        s->other = 1;
                        s->value = DldSysUndefSymbol;
                        *(volatile int *)&l2->prev = 0;
                        *(volatile int *)&l2->next = 0;
                        l2 = nx;
                    }
                    DeleteStrHashKey(B_00054398, e);
                }
                e++;
            }
            iosFree(m->exps);
            m->exps = 0;
        }
        l = m->links;
        if (l != 0) {
            n2 = m->tab->count;
            while (n2--) {
                unsigned int p = l->prev;
                Link *nx = l->next;
                Sym *s;
                if (p != 0) {
                    if (p & 0x80000000)
                        ((Link *)(p & 0x7FFFFFFF))->sym = (Sym *)nx;
                    else
                        ((Link *)p)->next = nx;
                }
                if (nx != 0)
                    nx->prev = p;
                s = l->sym;
                *(volatile int *)&l->next = 0;
                *(volatile int *)&l->prev = 0;
                l++;
                s->other = 1;
                s->value = DldSysUndefSymbol;
            }
            iosFree(m->links);
            m->links = 0;
        }
        m->flags &= 0x7FFFFFFF;
    }
}
