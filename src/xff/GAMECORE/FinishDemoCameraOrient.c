extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void isysRequestDeleteObj(void *);

void FinishDemoCameraOrient(char *d)
{
    void *last = 0;
    void **e;
    for (e = isysGroupForFirst(d, 0); e != 0; e = isysGroupForNext(e, 0))
        last = *e;
    if (last != 0)
        isysGroupForExit(last, 0);
    isysRequestDeleteObj(*(void **)(d + 0x28));
}
