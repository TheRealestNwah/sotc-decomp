typedef struct { int hash; int a, b; int next; } StrKey;
typedef struct { int size; int tbl; } StrHash;

void AddStrHashKey(StrHash *h, StrKey *k)
{
    int hash = k->hash;
    k->next = ((int *)h->tbl)[hash & (h->size - 1)];
    ((int *)h->tbl)[hash & (h->size - 1)] = (int)k;
}
