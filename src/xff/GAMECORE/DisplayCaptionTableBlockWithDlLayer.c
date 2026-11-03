extern int rootPtn;
extern char *D_00179FF4;
extern int D_00179FF8;
extern char RO_0017CA88[];
extern char *iosMallocAlign(void *, int, int);
extern void func_000118C8(void *);
extern void D_00012210(void *) __attribute__((weak));
extern int gcCreateScriptObj(void (*)(void *), void *, void *, int, int, int, char *);
extern void SetScriptObjDeleteCallBackFunc(int, void (*)(void *), void *);

int DisplayCaptionTableBlockWithDlLayer(int table, int a1, int a2, int a3, int *layer)
{
    char *c = iosMallocAlign(&rootPtn, 0x1C, 0x10);
    void (*cb)(void *);
    int obj;

    *(int *)(c + 0x0) = table;
    *(int *)(c + 0x4) = a1;
    *(int **)(c + 0x8) = layer;
    if (layer != 0)
        *layer = 0;
    *(int *)(c + 0xC) = a2;
    *(int *)(c + 0x10) = a3;
    *(int *)(c + 0x14) = 0;
    *(char **)(c + 0x18) = D_00179FF4;
    D_00179FF4 = c;
    D_00179FF8++;
    cb = D_00012210;
    obj = gcCreateScriptObj(func_000118C8, c, &rootPtn, 0x1000, 0, 0xA, RO_0017CA88);
    if (cb != 0)
        SetScriptObjDeleteCallBackFunc(obj, cb, c);
    return obj;
}
