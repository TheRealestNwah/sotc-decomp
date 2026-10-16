extern char D_0017A3AC[];
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(int, int);
extern int getModuleSize(int);

void seamlessstage_mallocerrorfunc(void)
{
    int m = 0;
    int *g;

    for (g = isysGroupForFirst(D_0017A3AC, 0); g != 0; g = isysGroupForNext(g, 0)) {
        m = *g;
        getModuleSize(m);
    }
    if (m != 0)
        isysGroupForExit(m, 0);
}
