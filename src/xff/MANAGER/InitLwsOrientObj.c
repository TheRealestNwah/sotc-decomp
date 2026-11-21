typedef union { float f; int i; } FI;
typedef struct LwsDef {
    int q[3][4];
    int count;
    int extra;
    FI scale;
    char pad3C[4];
} LwsDef;

extern int DldSysUndefSymbol;
extern char *GetScrLwsOriClass(unsigned char *);
extern LwsDef *GetScriptLwsOrientDefinfo(int);
extern void *iosMallocAlign(int, int, int);
extern void iosUnitMatrix(void *);
extern void CharacterClassMalloc(int, char *, int, int);
extern void _isysCreateSubMsgQueue(void *, void *, int, int);
extern void InitCharacterObj(unsigned char *, int *);
extern void func_00080860(unsigned char *, int *, char *, void *, LwsDef *, int *, char *, int);

#define DEF ((LwsDef *)*(int *)(cls + 0x11F8))
static inline int resolveRef(int *ref)
{
    int r = *ref & 0x3FFFF;
    int *b = r ? *(int **)((char *)ref - r) : 0;
    return (b && b != (int *)DldSysUndefSymbol) ? b[4] : 0;
}

int InitLwsOrientObj(unsigned char *obj, int *def)
{
    int heap;
    int n;
    char *cls;
    char *cc;
    int *ref;
    register LwsDef *info __asm__("$23");
    void *tail;
    int *w;
    int i;

    ref = (int *)def[71];
    heap = *(int *)obj;
    n = def[74];
    cls = GetScrLwsOriClass(obj);
    cc = cls + 0x70;
    info = GetScriptLwsOrientDefinfo(*(int *)(resolveRef(ref + 4) + 0x28));
    *(int *)(cls + 0x11F8) = (int)info;
    tail = (char *)info + 0x3C;
    *(int **)(cls + 0x1200) = iosMallocAlign(*(int *)obj, n * 0x50, 0x10);
    w = *(int **)(cls + 0x1200);
    DEF->count = n;
    DEF->extra = def[76];
    DEF->scale.f = ((FI *)&def[75])->f;
    ((FI *)(cls + 0x1218))->f = 1.0f;
    __asm__ __volatile__("sqc2 $vf0, 0(%0)" : : "r"(DEF->q[0]) : "memory");
    __asm__ __volatile__("sqc2 $vf0, 0(%0)" : : "r"(DEF->q[1]) : "memory");
    __asm__ __volatile__("sqc2 $vf0, 0(%0)" : : "r"(DEF->q[2]) : "memory");
    {
        int cnt;
        LwsDef *d = DEF;
        cnt = d->count + (d->extra != 0);
        *(int *)(cls + 0x11FC) = def[71];
        *(int *)(cc + 0x354) = 0;
        *(int *)(cc + 0x358) = 0;
        CharacterClassMalloc(heap, cc, cnt, 0);
    }
    for (i = 0; i < n; i++) {
        iosUnitMatrix(*(void **)(cc + 0x2D8));
        *w = 0;
        w += 20;
    }
    *(int *)(cc + 0x300) = 0;
    _isysCreateSubMsgQueue(cc + 0x10D0, iosMallocAlign(heap, 0x300, 4), 0x60, 8);
    if (!def[38]) {
        def[1] = 1;
    } else {
        def[1] = n;
    }
    InitCharacterObj(obj, def);
    {
        LwsDef *d = *(LwsDef **)(cls + 0x11F8);
        if (d->extra) {
            *(int *)(cc + 0x378) = d->count;
        }
    }
    *(int *)(cls + 0x1224) = -1;
    *(int *)(cls + 0x1220) = -1;
    *(int *)(cls + 0x121C) = -1;
    func_00080860(obj, def, cls, tail, info, def, cc, n);
    return 1;
}
