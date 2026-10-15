typedef struct { char pad[0xC]; int n; int list; } HydeList;
extern HydeList SH_PlayerHydeObjListPlayerHydeList;
extern void parseHydeObject(void *, int, int, int, int);

int nico_hydePlayerByNearClip(void *a, int b)
{
    HydeList *h = &SH_PlayerHydeObjListPlayerHydeList;
    if (h->n != 0)
        parseHydeObject(a, h->list, h->n, b, 7);
    return 0;
}
