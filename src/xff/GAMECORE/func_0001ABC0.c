extern char gcGlobalVar[];
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(void *, int);
extern void isysRequestDeleteObj(void *);
extern void scrRun(void);
extern void scrRunM(int);

static inline void deleteGroupObjs(void *group)
{
    void *o = 0;
    int *g;

    for (g = isysGroupForFirst(group, 0); g != 0; g = isysGroupForNext(g, 0)) {
        o = (void *)*g;
        isysRequestDeleteObj(o);
    }
    if (o != 0)
        isysGroupForExit(o, 0);
}

static void func_0001ABC0(void *group)
{
    deleteGroupObjs(gcGlobalVar + 0x278);
    deleteGroupObjs(gcGlobalVar + 0x27C);
    deleteGroupObjs(group);
    for (;;) {
        int n = 0;
        void *o = 0;
        int *g;

        for (g = isysGroupForFirst(group, 0); g != 0; g = isysGroupForNext(g, 0)) {
            o = (void *)*g;
            n++;
        }
        if (o != 0)
            isysGroupForExit(o, 0);
        if (n == 0)
            break;
        scrRun();
    }
    scrRunM(30);
}
