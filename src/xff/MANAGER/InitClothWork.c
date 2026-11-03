#ifdef NONMATCHING /* 5 diffs: store order of the cloth work header fields; no source order of the five stores matches */
extern char *GetLayoutClass(void *);
extern void *iosMallocAlign(void *, int, int);
static int func_000BD050(char *, void *, short *, void *);

typedef struct ClothWork {
    char *items;
    short count;
    unsigned char flag6;
    unsigned char flag7;
    unsigned char flag8;
    char pad9[3];
    int c;
    int d;
    int b;
} ClothWork;

ClothWork *InitClothWork(void *heap, void *o, int *def)
{
    int n = 0;
    char *cls = GetLayoutClass(o);
    short *d = *(short **)(cls + 0x180);
    short *e = d;
    ClothWork *cw;
    char *w;
    int i;

    while (*e >= 0) {
        e += 0x1A;
        n++;
    }
    cw = iosMallocAlign(heap, 0x18, 4);
    w = iosMallocAlign(heap, n * 0x90, 0x10);
    cw->count = n;
    cw->items = w;
    cw->flag7 = 1;
    cw->flag6 = 0;
    cw->flag8 = 1;
    *(ClothWork **)(cls + 0x178) = cw;
    for (i = 0; i < n; i++) {
        cw->flag6 |= func_000BD050(w, heap, d, o);
        w += 0x90;
        d += 0x1A;
    }
    if (def[4])
        ((void (*)(void *))def[4])(o);
    cw->b = def[5];
    cw->c = def[6];
    cw->d = def[7];
    return cw;
}
#endif
