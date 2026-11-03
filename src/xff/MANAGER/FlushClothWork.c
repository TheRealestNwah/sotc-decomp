extern char *GetLayoutClass(void *);
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void isysRequestDeleteObj(void *);
extern void isysDeleteGroupAllObj(void *);
extern void meshObjectFree(void *);

void FlushClothWork(void *o)
{
    int n = 0;
    char *cls = GetLayoutClass(o);
    short *d = *(short **)(cls + 0x180);
    char *w = **(char ***)(cls + 0x178);
    short *e = d;
    int i;

    while (*e >= 0) {
        e += 0x1A;
        n++;
    }
    for (i = 0; i < n; i++) {
        switch (*d) {
        case 0:
        default:
            meshObjectFree(*(void **)(w + 0x24));
            break;
        case 1: {
            void **node;
            void *last = 0;
            for (node = isysGroupForFirst(w + 8, 0); node != 0; node = isysGroupForNext(node, 0)) {
                last = *node;
                isysRequestDeleteObj(last);
            }
            if (last != 0)
                isysGroupForExit(last, 0);
            isysDeleteGroupAllObj(w + 8);
            break;
        }
        }
        d += 0x1A;
        w += 0x90;
    }
}
