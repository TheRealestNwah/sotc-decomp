extern int B_0014E888[];
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(int, int);

void windowDeleteAllObjByGroup(int grp)
{
    int o = 0;
    int *g;
    char *w;

    for (g = isysGroupForFirst(&B_0014E888[grp], 0); g != 0; g = isysGroupForNext(g, 0)) {
        o = *g;
        w = (char *)o + 0x20;
        if (w != 0)
            *(int *)(w + 0x1CC) = 1;
    }
    if (o != 0)
        isysGroupForExit(o, 0);
}
