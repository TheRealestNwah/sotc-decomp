typedef struct ScriptClass {
    char pad0[0x24];
    int entry;
    unsigned char state;
    unsigned char flags;
    char pad2A[0xE];
    int reset;
    int *env;
    char pad40[0xC];
    void (*done)(void *, int);
    int doneArg;
} ScriptClass;

extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern ScriptClass *GetScriptClass(void *);
extern void isysInitSubThreadExecEnv(void *, int);
extern int isysWakeupSubThread(void *);
extern int isysStartSubThread(void *, int);
extern void isysLetterObjDiscardLetterAll(void *);
extern void isysRequestDeleteObj(void *);

static void func_000873A8(void *group)
{
    void **node;
    void *obj = 0;

    for (node = isysGroupForFirst(group, 0); node != 0; node = isysGroupForNext(node, 0)) {
        ScriptClass *c;
        int r;

        obj = *node;
        c = GetScriptClass(obj);
        if (c->reset != 0) {
            c->state = 0;
            isysInitSubThreadExecEnv(obj, c->env[1]);
            c->reset = 0;
        }
        if (c->state == 1) {
            r = isysWakeupSubThread(obj);
        } else if (c->state == 0) {
            c->state = 1;
            r = isysStartSubThread(obj, c->entry);
        } else {
            r = 0;
            isysLetterObjDiscardLetterAll(obj);
        }
        if (r != 0) {
            if (c->done != 0)
                c->done(obj, c->doneArg);
            c->state = 2;
            if (!(c->flags & 1))
                isysRequestDeleteObj(obj);
        }
    }
    if (obj != 0)
        isysGroupForExit(obj, 0);
}
