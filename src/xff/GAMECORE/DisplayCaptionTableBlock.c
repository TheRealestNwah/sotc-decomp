/* Creates a caption table block (0x1C bytes) linked into the caption block list and starts its script object, as a child of parent when given. Loading the 0x19 type through a local assigned after the first store keeps the Original's register allocation. */
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
    int k19;
    char *c = iosMallocAlign(&rootPtn, 0x1C, 0x10);
    void (*fn)(void *);
    void (*cb)(void *);
    char *name;
    int obj;

    *(int *)(c + 0x0) = table;
    k19 = 0x19;
    *(int *)(c + 0x4) = parent;
    *(int **)(c + 0x8) = layer;
    if (layer != 0)
        *layer = 0;
    *(int *)(c + 0xC) = a2;
    *(int *)(c + 0x10) = k19;
    *(int *)(c + 0x14) = 0;
    *(char **)(c + 0x18) = D_00179FF4;
    D_00179FF4 = c;
    D_00179FF8++;
    fn = func_000118C8;
    cb = D_00012210;
    name = RO_0017CA88;
    if (parent != 0)
        obj = _gcCreateChildScriptObj(fn, c, &rootPtn, 0x1000, 0, 0xA, name, parent);
    else
        obj = gcCreateScriptObj(fn, c, &rootPtn, 0x1000, 0, 0xA, RO_0017CA88);
    if (cb != 0)
        SetScriptObjDeleteCallBackFunc(obj, cb, c);
    return obj;
}
