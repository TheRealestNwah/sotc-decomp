extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(void *, int);
extern char gcGlobalVar[];

void *GAMEUTIL_get_boss_obj(void)
{
    void *found = 0;
    void *o = 0;
    int *g;

    for (g = isysGroupForFirst(gcGlobalVar + 0x2B8, 0); g != 0; g = isysGroupForNext(g, 0)) {
        o = (void *)*g;
        found = o;
        break;
    }
    if (o != 0)
        isysGroupForExit(o, 0);
    return found;
}
