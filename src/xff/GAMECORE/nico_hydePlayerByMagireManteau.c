typedef struct { char pad[0xC]; int n; int list; } HydeList;
extern HydeList SH_PlayerHydeObjListPlayerHydeList;
extern void parseHydeObject(void *, int, int, int, int);

void nico_hydePlayerByMagireManteau(void *a, int b)
{
    HydeList *h = &SH_PlayerHydeObjListPlayerHydeList;
    if (h->n != 0)
        parseHydeObject(a, h->list, h->n, b, 3);
}
