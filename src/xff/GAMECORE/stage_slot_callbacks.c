extern void func_00027070(int);
extern void func_00026E38(int);
extern void func_000272A8(int);
extern void func_00027968(int);
extern void func_00026AB8(int);
extern void *createScriptObj(void (*)(int), int, void *, int, int, int, int, int);
extern int isysAddGroupWithLinkParam(void *, void *, int, int);
extern char gcGlobalVar[], B_00188730[];
static void func_0002D458(int handle)
{
    func_00027070(handle);
    func_00026E38(handle);
}
static void func_0002D480(int handle)
{
    void *object;
    func_000272A8(handle);
    object = createScriptObj(func_00026AB8, handle, *(void **)(gcGlobalVar + 0x308),
        0x1000, 0, 1, 0, 0);
    isysAddGroupWithLinkParam(object, B_00188730, 0, 0);
    func_00026E38(handle);
    func_00027968(handle);
}