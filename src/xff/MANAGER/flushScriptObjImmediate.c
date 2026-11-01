extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void isysRequestDeleteObj(void *);
extern void isysDeleteGroupAllObj(void *);

typedef struct {
    char pad0[0x30];
    char group[0x24];
    void (*func)(void *, int);
    int funcArg;
    void (*deleteFunc)(void *, int);
    int deleteArg;
} ScriptClass;

extern ScriptClass *GetScriptClass(void *);

void flushScriptObjImmediate(void *obj)
{
    ScriptClass *s = GetScriptClass(obj);
    void *object;
    void **entry;

    if (s->func) {
        s->func(obj, s->funcArg);
    }
    if (s->deleteFunc) {
        s->deleteFunc(obj, s->deleteArg);
    }
    object = 0;
    for (entry = isysGroupForFirst(s->group, 0); entry != 0;
         entry = isysGroupForNext(entry, 0)) {
        object = *entry;
        isysRequestDeleteObj(object);
    }
    if (object != 0)
        isysGroupForExit(object, 0);
    isysDeleteGroupAllObj(s->group);
}
