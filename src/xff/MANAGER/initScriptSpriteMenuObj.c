/* Parked: 11 diffs. Only scheduling differs: the Original issues the sheetFsLanguageCode lui/lw before the stack adjust and $ra save, and loads src[0] earlier. Permuter not yet run. */
#ifdef NONMATCHING
extern int sheetFsLanguageCode;
extern int DldSysUndefSymbol;

typedef struct {
    int w0;
    int sym;
    int *lang;
    float f0, f1, f2, f3, f4, f5;
    int w24;
    int w28;
    int w2C;
    int w30;
    int w34;
    int w38;
    int w3C;
    int w40;
    int w44;
    int w48;
    int w4C;
} SpriteMenuDef;

extern void *CreateScriptSpriteMenuObj(void *heap, int extra, SpriteMenuDef def);

static inline int symVal(int *h)
{
    unsigned int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return (t != 0 && t != (int *)DldSysUndefSymbol) ? t[3] : 0;
}

void *initScriptSpriteMenuObj(void *heap, int *src, int a2, int a3, int t0, int t1)
{
    SpriteMenuDef d = {
        src[0],
        symVal(src + sheetFsLanguageCode),
        src + sheetFsLanguageCode,
        ((float *)src)[6], ((float *)src)[7], ((float *)src)[8], ((float *)src)[9], ((float *)src)[10], ((float *)src)[11],
        src[12],
        src[5],
        src[2],
        a2,
        src[3],
        t0,
        a3,
        t1,
        0, 0, 0,
    };
    return CreateScriptSpriteMenuObj(heap, src[4], d);
}
#endif
