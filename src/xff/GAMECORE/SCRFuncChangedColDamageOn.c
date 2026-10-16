extern int DldSysUndefSymbol;
extern void *GetCollisionResource(void *);
extern void ChangeCollisionResourceAttribute(void *, int, int, int, int, int, int);

void SCRFuncChangedColDamageOn(void *a, int b, int c, int d, int e, int f, unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    ChangeCollisionResourceAttribute(GetCollisionResource((t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0), d, e, 8, 0, 8, 8);
}
