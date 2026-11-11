/* Parked: 95 diffs. DLD handle walk; the original does not reuse the encoded handle word and
   numbers its registers differently (count in $t1, current kind in $a3, base in $t0). */
#ifdef NONMATCHING
extern int DldSysUndefSymbol;
extern int MotionKind_ALWAYS;

typedef struct {
    char pad0[8];
    char *type;
    char padC[4];
    char *data;
} DldTable;

typedef struct Kind {
    char pad[0xD4];
    unsigned int *next;
    int count;
} Kind;

static inline int dldCount(unsigned int *h)
{
    unsigned int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? *(int *)((char *)t + 0xC) : 0;
}

static inline unsigned int *dldFirst(unsigned int *h)
{
    unsigned int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? (unsigned int *)t->data : 0;
}

static inline Kind *dldKind(unsigned int *h)
{
    unsigned int enc = *h;
    unsigned int off = enc & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    if (t != 0 && t != (DldTable *)DldSysUndefSymbol)
        return (Kind *)(t->data + ((enc >> 18) & 0xFFF) * *(int *)(t->type + 0xC));
    return 0;
}

void OptimizeMotionOrient(unsigned int *h)
{
    int n = dldCount(h);
    if (n != 0) {
        unsigned int *first = dldFirst(h);
        unsigned int *base = first;
        Kind *cur = dldKind(first);
        int i = n - 2;
        unsigned int *p = base + 7;
        if (i != -1) {
            do {
                Kind *k = dldKind(p);
                if (k != cur && (int)cur != MotionKind_ALWAYS) {
                    cur->next = base;
                    {
                        int d = (int)((p - 7) - base);
                        base = p;
                        cur->count = d * 0xB6DB6DB7 + 1;
                    }
                    cur = k;
                }
                i--;
                p += 7;
            } while (i != -1);
        }
        if ((int)cur != MotionKind_ALWAYS) {
            cur->next = base;
            cur->count = (int)((p - 7) - base) * 0xB6DB6DB7 + 1;
        }
    }
}
#else
extern void OptimizeMotionOrient(unsigned int *);
#endif
