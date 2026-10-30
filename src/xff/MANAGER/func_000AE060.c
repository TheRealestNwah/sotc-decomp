typedef struct {
    unsigned short id;
    char pad2[0x14 - 2];
} PrimA;

typedef struct {
    char pad0[0x30];
    int id;
} PrimB;

typedef struct {
    char pad0[0x3C];
    int id;
} LayNode;

typedef struct {
    char pad0[8];
    unsigned char kind;
    char pad9[0x14 - 9];
    void *prims;
    char pad18[0x54 - 0x18];
    int *map;
    char pad58[0x90 - 0x58];
} LayEntry;

typedef struct {
    char pad0[8];
    LayEntry *entries;
    char padC[0x18 - 0xC];
    LayNode *nodes;
} Layout;

typedef struct {
    char pad0[0x184];
    struct {
        char pad0[0x20];
        Layout *layout;
    } *res;
} LayoutClass;

typedef struct {
    void *obj;
    unsigned int ref;
} LayRef;

extern LayoutClass *GetLayoutClass(void *);

static int func_000AE060(LayRef *r)
{
    int ent = (r->ref >> 24) & 0x7F;
    int sub = r->ref & 0xFFFFFF;
    Layout *lay = GetLayoutClass(r->obj)->res->layout;
    int id;

    if ((int)r->ref < 0) {
        LayEntry *e = &lay->entries[ent];
        if (e->kind)
            id = ((PrimA *)e->prims)[sub].id;
        else
            id = ((PrimB *)e->prims)[sub].id;
    } else {
        id = lay->nodes[lay->entries[ent].map[sub]].id;
    }
    return id;
}
