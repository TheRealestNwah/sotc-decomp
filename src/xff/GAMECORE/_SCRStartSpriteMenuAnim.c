extern char rootPtn[];
extern int *iosMallocAlign(void *, int, int);
extern void initScriptSpriteMenuObj(void *, int, int *, int, int, int);

void _SCRStartSpriteMenuAnim(int def, int b, int c, int d, int e, int f)
{
    int *p = iosMallocAlign(rootPtn, 16, 16);

    p[3] = c;
    p[0] = d;
    p[1] = e;
    p[2] = f;
    initScriptSpriteMenuObj(rootPtn, def, p, b, 9, 0);
}
