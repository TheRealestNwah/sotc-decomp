extern char symbolDefModuleGroup[];
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);

int isysGetSymdefModuleObjNum(void)
{
    void *last = 0;
    int n = 0;
    void **e;
    for (e = isysGroupForFirst(symbolDefModuleGroup, 0); e != 0; e = isysGroupForNext(e, 0)) {
        last = *e;
        n++;
    }
    if (last != 0)
        isysGroupForExit(last, 0);
    return n;
}
