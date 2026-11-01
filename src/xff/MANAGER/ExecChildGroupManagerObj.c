extern char *GetScriptAnimationClass(void *);
extern char *GetScrLwsOriClass(void *);
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(void *, int);
extern void isysDeleteGroupAllObj(void *);

void ExecChildGroupManagerObj(unsigned char *p, void (*fn)(void *))
{
    char *m;
    int *g;
    void *o;

    switch (p[8]) {
    case 0xD:
        m = GetScriptAnimationClass(p) + 0x320;
        break;
    case 0x16:
        m = GetScrLwsOriClass(p) + 0x11F0;
        break;
    default:
        m = 0;
        break;
    }
    if (*m != 0) {
        o = 0;
        for (g = isysGroupForFirst(m + 2, 0); g != 0; g = isysGroupForNext(g, 0)) {
            o = (void *)*g;
            fn(o);
        }
        if (o != 0)
            isysGroupForExit(o, 0);
        isysDeleteGroupAllObj(m + 2);
        *m = 0;
    }
}
