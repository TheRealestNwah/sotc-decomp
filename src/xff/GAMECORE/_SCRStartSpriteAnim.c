extern char rootPtn[];
extern int *iosMallocAlign(void *, int, int);
extern void initScriptSpriteObj(void *, int, int *, int, int, int);

void _SCRStartSpriteAnim(int def, int b, int c, int d, int e, int f)
{
    int *p = iosMallocAlign(rootPtn, 16, 16);

    p[3] = c;
    p[0] = d;
    p[1] = e;
    p[2] = f;
    initScriptSpriteObj(rootPtn, def, p, b, 9, 0);
}
