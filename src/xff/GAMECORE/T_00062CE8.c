extern char gcGlobalVar[];
extern int **isysGroupForFirst(void *, int);
extern int **isysGroupForNext(void *, int);
extern void isysGroupForExit(int *, int);
extern void unloadObj(int *);

static void T_00062CE8(void)
{
    int *obj = 0;
    int **e;
    for (e = isysGroupForFirst(gcGlobalVar + 0x304, 0); e != 0; e = isysGroupForNext(e, 0)) {
        obj = *e;
        unloadObj(obj);
    }
    if (obj != 0) {
        isysGroupForExit(obj, 0);
    }
}
