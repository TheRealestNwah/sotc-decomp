extern int D_0017A348;
extern int D_0017A3AC;
extern char gcGlobalVar[];
extern void func_00024A78(void);
extern void *createScriptObj(void (*)(void), void *, int, int, int, int, int, int);
extern int **isysGroupForFirst(void *, int);
extern int **isysGroupForNext(void *, int);
extern void isysGroupForExit(void *, int);
extern void isysSleepSubThread(void);

void UnloadAllSeamlessStageObject(int arg)
{
    int req[2];

    if (D_0017A348 == 0)
        return;
    req[1] = arg;
    req[0] = 1;
    createScriptObj(func_00024A78, req, *(int *)(gcGlobalVar + 0x308), 0x4000, 0, 1, 0, 0);
    for (;;) {
        int **g;
        int n = 0;
        int *last = 0;

        for (g = isysGroupForFirst(&D_0017A3AC, 0); g != 0; g = isysGroupForNext(g, 0)) {
            last = *g;
            n++;
        }
        if (last != 0)
            isysGroupForExit(last, 0);
        if (n == 0 && req[0] == 0)
            break;
        isysSleepSubThread();
    }
}
