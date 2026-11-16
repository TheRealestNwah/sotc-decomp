typedef struct {
    char pad0[0x10];
    int flags;
    int id;
    int sub;
} Obj;

typedef struct {
    Obj *obj;
    char pad4[0x1C - 0x4];
} Entry;

typedef struct {
    char pad0[4];
    Entry *entries;
    unsigned int pad8_0 : 4;
    unsigned int count : 10;
    unsigned int pad8_14 : 18;
    char padC[0x38 - 0xC];
    int pad38_0 : 11;
    int id : 10;
    int sub : 10;
    int pad38_31 : 1;
} Table;

static inline Entry *findById(Table *t, Entry *list)
{
    int j;

    for (j = 0; j < t->count; j++) {
        if ((list[j].obj->flags & 2) && list[j].obj->id == t->id)
            return &list[j];
    }
    return 0;
}

static Entry *func_00093E40(Table *t)
{
    int i;

    for (i = 0; i < t->count; i++) {
        Entry *e = &t->entries[i];
        Obj *o = e->obj;

        if (o->flags & 0x100)
            return findById(t, t->entries);
        if ((o->flags & 2) && o->id == t->id && o->sub == t->sub)
            return e;
    }
    return 0;
}
