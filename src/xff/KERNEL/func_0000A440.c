typedef struct {
    void *ptr;
    char pad4[0x18 - 4];
    int used;
    char pad1C[0x20 - 0x1C];
} Entry;

typedef struct {
    char pad0[0x30];
    Entry *entries;
    char pad34[0x40 - 0x34];
    int count;
} Table;

typedef struct {
    int a;
    void *p;
} Buf;

typedef struct {
    char pad0[0x1C];
    Table *table;
    char pad20[0x2C - 0x20];
    unsigned int flags;
    Buf buf;
    char pad38[0x3C - 0x38];
    int size;
} Obj;

extern volatile int D_00040900;
extern void iosFree(void *p);
extern void func_00008108(Obj *o);

static void func_0000A440(Obj *o)
{
    if (o->flags & 0x40000000) {
        iosFree(((void **)o->table)[1]);
        func_00008108(o);
    } else {
        Table *t;
        Buf *b = &o->buf;
        if (b->p) {
            iosFree(b->p);
            b->a = 0;
        }
        func_00008108(o);
        t = o->table;
        if (t) {
            int n = t->count - 2;
            Entry *e = t->entries + 1;
            for (; n != -1; n--, e++) {
                if (e->used) {
                    e->used = 0;
                    iosFree(e->ptr);
                }
            }
            iosFree(t);
        }
    }
    D_00040900 -= o->size;
}
