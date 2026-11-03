extern int DldSysUndefSymbol;
extern int **GetAnimationClass(void);
extern void func_0006F488(int, int, float, int, float, float, int, float, int);
void xzfit(int a, int b, float f0, int c, float f1, float f2, int d, float f3, int e)
{
    unsigned int *h = (unsigned int *)(*GetAnimationClass() + 3);
    int off = *h & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    char *dyn = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) : 0;
    func_0006F488(a, b, f0, c, f1, f2, d, f3, e);
}
