extern void func_0001FA68();
extern void func_0001FA70();
extern void *_isysCreateObj(void *, int, int, int, int, int);
extern void isysSetObjImmediateDeleteFunc(void *, void *);

void *CreateMeshObj(void *heap, int a, void *b)
{
    void *o = _isysCreateObj(heap, 0x23, 0x90, (int)b, (int)func_0001FA68, 0x10);
    isysSetObjImmediateDeleteFunc(o, func_0001FA70);
    return o;
}
