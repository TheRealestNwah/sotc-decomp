typedef struct {
    void *buf;
    char pad4[0x14];
    int used;
    char pad1C[4];
} Entry;

typedef struct {
    char pad0[0x30];
    Entry *entries;
    char pad34[0xC];
    int count;
} Table;

typedef struct {
    int head;
    void *buf;
} Buffer;

typedef struct {
    char pad0[0x1C];
    Table *table;
    char pad20[0xC];
    unsigned int flags;
    Buffer sub;
} Obj;

extern void iosFree(void *);
extern void func_00008108(Obj *);

static void func_0000A350(Obj *o)
{
    Table *t;

    if (o->flags & 0x40000000) {
        iosFree(*(void **)((char *)o->table + 4));
        func_00008108(o);
        return;
    }
    {
        Buffer *sub = &o->sub;

        if (sub->buf) {
            iosFree(sub->buf);
            sub->head = 0;
        }
    }
    func_00008108(o);
    t = o->table;
    if (t) {
        Entry *e = &t->entries[1];
        int n = t->count - 1;

        while (n--) {
            if (e->used) {
                e->used = 0;
                iosFree(e->buf);
            }
            e++;
        }
        iosFree(t);
    }
}
