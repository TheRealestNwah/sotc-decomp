extern int DldSysUndefSymbol;
extern char *bgmAutoStart(void *, int, void *, int);
extern void func_0012B060();

void SCRFuncSoundPlay(void *a, int b, int c, int d, int e, int f, unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    char *r = bgmAutoStart((t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0, 0, func_0012B060, 0);
    *(char **)(r + 0x30) = r;
}
