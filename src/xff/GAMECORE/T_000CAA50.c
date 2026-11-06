extern char gcGlobalVar[];
extern int *isysGroupForFirst(char *, int);
extern int *isysGroupForNext(int *, int);
extern void unloadObj(int);
extern void isysGroupForExit(int, int);

static void T_000CAA50(void)
{
    int *g;
    int last = 0;

    for (g = isysGroupForFirst(gcGlobalVar + 0x304, 0); g != 0; g = isysGroupForNext(g, 0)) {
        last = *g;
        unloadObj(last);
    }
    if (last != 0)
        isysGroupForExit(last, 0);
}
