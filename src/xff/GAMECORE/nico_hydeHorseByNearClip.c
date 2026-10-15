typedef struct { char pad[0xC]; int n; int list; } HydeList;
extern HydeList SH_PlayerHydeObjListHorseHydeList;
extern void parseHydeObject(void *, int, int, int, int);

int nico_hydeHorseByNearClip(void *a, int b)
{
    HydeList *h = &SH_PlayerHydeObjListHorseHydeList;
    if (h->n != 0)
        parseHydeObject(a, h->list, h->n, b, 7);
    return 0;
}
