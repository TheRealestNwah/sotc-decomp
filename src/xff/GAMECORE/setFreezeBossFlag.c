extern char gcGlobalVar[];
extern unsigned char D_00179A50;
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(int, int);
extern char *GetCharacterClass(int);

void setFreezeBossFlag(void)
{
    int o = 0;
    int *g;

    for (g = isysGroupForFirst(gcGlobalVar + 0x2B8, 0); g != 0; g = isysGroupForNext(g, 0)) {
        o = *g;
        *(GetCharacterClass(o) + 0x2B4) = D_00179A50;
    }
    if (o != 0)
        isysGroupForExit(o, 0);
}
