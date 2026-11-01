typedef struct {
    char pad0[0x54];
    int base;
    int index;
} WindowDef;

extern void *_isysCreateObj(void *, int, int, int, void *, int);
extern void isysSetObjImmediateDeleteFunc(void *, void *);
extern void func_000DB490(void);
extern void D_000DB4A8(void);
extern void D_000DB500(void *);
extern void func_000DB0B8(void *, WindowDef *, void *, int, int, int);

void *CreateWindowObj(void *heap, WindowDef *def, void *thread, int arg)
{
    void *obj = _isysCreateObj(heap, 0xC, 0x420, def->base + def->index * 259 + 0x4703, func_000DB490, 0x10);

    isysSetObjImmediateDeleteFunc(obj, D_000DB500);
    func_000DB0B8(obj, def, thread ? thread : (void *)D_000DB4A8, 0x41A0, 3, arg);
    return obj;
}
