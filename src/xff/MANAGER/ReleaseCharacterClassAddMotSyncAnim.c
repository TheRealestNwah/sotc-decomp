extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(int, int);
extern void isysRequestDeleteObj(int);
extern void isysDeleteGroupAllObj(void *);

void ReleaseCharacterClassAddMotSyncAnim(void *grp)
{
    int o = 0;
    int *g;

    for (g = isysGroupForFirst(grp, 0); g != 0; g = isysGroupForNext(g, 0)) {
        o = *g;
        isysRequestDeleteObj(o);
    }
    if (o != 0)
        isysGroupForExit(o, 0);
    isysDeleteGroupAllObj(grp);
}
