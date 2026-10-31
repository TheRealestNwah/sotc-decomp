extern void flushScriptObjImmediate(void *);
extern void *isysGroupForFirst(void *, int);
extern void *isysGroupForNext(void *, int);
extern void isysGroupForExit(void *, int);
extern void isysRequestDeleteObj(void *);
extern void isysDeleteGroupAllObj(void *);

static void func_0007E8E8(char *o)
{
    void *obj = 0;
    void **it;

    flushScriptObjImmediate(o);
    for (it = isysGroupForFirst(o + 0xB8, 0); it != 0; it = isysGroupForNext(it, 0)) {
        obj = *it;
        isysRequestDeleteObj(obj);
    }
    if (obj != 0) {
        isysGroupForExit(obj, 0);
    }
    isysDeleteGroupAllObj(o + 0xB8);
}
