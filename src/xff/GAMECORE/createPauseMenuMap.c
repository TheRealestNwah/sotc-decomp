typedef struct Ptn Ptn;
extern Ptn rootPtn;
extern int D_0017B370[];
extern void *D_0017B394;
static void func_000D1340(void);
extern void *gcCreateScriptObj(void *, int, Ptn *, int, int, int, const char *);

void createPauseMenuMap(void)
{
    D_0017B370[0] = 0;
    D_0017B370[1] = 0;
    D_0017B370[2] = 0;
    if (D_0017B394 == 0)
        D_0017B394 = gcCreateScriptObj(func_000D1340, 0, &rootPtn, 0x1000, 0, 8, "st_maplog");
}
