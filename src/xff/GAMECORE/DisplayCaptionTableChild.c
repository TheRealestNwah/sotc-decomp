extern int rootPtn;
extern char *D_00179FF4;
extern int D_00179FF8;
extern char RO_0017CA60[];
extern char *iosMallocAlign(void *, int, int);
extern void func_000118C8(void *);
extern void D_00012210(void *) __attribute__((weak));
extern int gcCreateScriptObj(void (*)(void *), void *, void *, int, int, int, char *);
extern int _gcCreateChildScriptObj(void (*)(void *), void *, void *, int, int, int, char *, int);
extern void SetScriptObjDeleteCallBackFunc(int, void (*)(void *), void *);

int DisplayCaptionTableChild(int table, int parent, int arg1)
{
    int time = 0x19;
    char *c = iosMallocAlign(&rootPtn, 0x1C, 0x10);
    void (*cb)(void *);
    void (*fn)(void *);
    void *root;
    char *name;
    int obj;

    *(int *)(c + 0x0) = table;
    *(int *)(c + 0xC) = arg1;
    *(int *)(c + 0x4) = parent;
    *(int *)(c + 0x10) = time;
    *(int *)(c + 0x8) = 0;
    *(int *)(c + 0x14) = 0;
    *(char **)(c + 0x18) = D_00179FF4;
    D_00179FF4 = c;
    D_00179FF8++;
    cb = D_00012210;
    name = RO_0017CA60;
    root = &rootPtn;
    fn = func_000118C8;
    if (parent != 0)
        obj = _gcCreateChildScriptObj(fn, c, root, 0x1000, 0, 0xA, name, parent);
    else
        obj = gcCreateScriptObj(fn, c, root, 0x1000, 0, 0xA, name);
    if (cb != 0)
        SetScriptObjDeleteCallBackFunc(obj, cb, c);
    return obj;
}
