extern void *GetLayoutObjGroup(void *);
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);

int GetLayoutObjNum(void *l)
{
    void *last = 0;
    int n = 0;
    void **e;
    for (e = isysGroupForFirst(GetLayoutObjGroup(l), 0); e != 0; e = isysGroupForNext(e, 0)) {
        last = *e;
        n++;
    }
    if (last != 0)
        isysGroupForExit(last, 0);
    return n;
}
