typedef struct Ent { int key; int a, b; struct Ent *next; } Ent;
typedef struct { int size; Ent **tbl; } Hash;

Ent *SearchStrHashKey(Hash *h, int key)
{
    Ent *e;
    for (e = h->tbl[key & (h->size - 1)]; e != 0; e = e->next) {
        if (key == e->key)
            return e;
    }
    return 0;
}
