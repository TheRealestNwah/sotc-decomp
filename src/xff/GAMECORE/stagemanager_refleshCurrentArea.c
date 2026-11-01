extern char gcGlobalVar[];
extern int B_00188668[];
extern char B_00188730[];
extern void func_0002D458(void);
extern void *createScriptObj(void *func, int id, int a2, int a3, int t0, int t1, int t2, int t3);
extern int isysAddGroupWithLinkParam(void *obj, void *grp, int a2, int a3);

void stagemanager_refleshCurrentArea(void)
{
    int i;

    for (i = 0; B_00188668[i] >= 0; i++) {
        /* Taking gcGlobalVar inside the loop keeps its full address in a
           saved register instead of folding 0x308 into the load. */
        char *g = gcGlobalVar;
        isysAddGroupWithLinkParam(
            createScriptObj(func_0002D458, B_00188668[i], *(int *)(g + 0x308), 0x1000, 0, 1, 0, 0),
            B_00188730, 0, 0);
    }
}
