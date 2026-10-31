typedef struct Ent { int key; int a, b; struct Ent *next; } Ent;
typedef struct { int size; Ent **tbl; } Hash;
extern void iosJumpRecoverPoint(void *, ...);
extern unsigned char RO_00044978[];

void DeleteStrHashKey(Hash *h, Ent *k)
{
    Ent *e;
    Ent *next;
    Ent *prev;

    prev = 0;
    e = h->tbl[k->key & (h->size - 1)];
    while (e != 0) {
        next = e->next;
        if (k == e) {
            if (prev == 0) {
                h->tbl[e->key & (h->size - 1)] = next;
            } else {
                prev->next = next;
            }
            return;
        }
        prev = e;
        e = next;
    }
    iosJumpRecoverPoint(RO_00044978);
}
