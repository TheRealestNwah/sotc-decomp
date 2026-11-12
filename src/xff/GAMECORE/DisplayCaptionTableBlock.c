#ifdef NONMATCHING
/* Parked: 7 words differ (register allocation of the hoisted addresses); permuter (40 min) found nothing below 7, and reordering the name/cb/fn temps gives 20+. */
extern int rootPtn;
extern char *D_00179FF4;
extern int D_00179FF8;
extern char RO_0017CA88[];
extern char *iosMallocAlign(void *, int, int);
extern void func_000118C8(void *);
extern void D_00012210(void *) __attribute__((weak));
extern int gcCreateScriptObj(void (*)(void *), void *, void *, int, int, int, char *);
extern int _gcCreateChildScriptObj(void (*)(void *), void *, void *, int, int, int, char *, int);
extern void SetScriptObjDeleteCallBackFunc(int, void (*)(void *), void *);

int DisplayCaptionTableBlock(int table, int parent, int a2, int *layer)
{
    char *c = iosMallocAlign(&rootPtn, 0x1C, 0x10);
    void (*fn)(void *);
    void (*cb)(void *);
    char *name;
    int obj;

    *(int *)(c + 0x0) = table;
    *(int *)(c + 0x4) = parent;
    *(int **)(c + 0x8) = layer;
    if (layer != 0)
        *layer = 0;
    *(int *)(c + 0xC) = a2;
    *(int *)(c + 0x10) = 0x19;
    *(int *)(c + 0x14) = 0;
    *(char **)(c + 0x18) = D_00179FF4;
    D_00179FF4 = c;
    D_00179FF8++;
    name = RO_0017CA88;
    cb = D_00012210;
    fn = func_000118C8;
    if (parent != 0)
        obj = _gcCreateChildScriptObj(fn, c, &rootPtn, 0x1000, 0, 0xA, name, parent);
    else
        obj = gcCreateScriptObj(fn, c, &rootPtn, 0x1000, 0, 0xA, RO_0017CA88);
    if (cb != 0)
        SetScriptObjDeleteCallBackFunc(obj, cb, c);
    return obj;
}
#endif
