/* Script objects: sub-thread objects grouped by priority, run once a frame
 * by execScript, with their finish and delete callbacks. */

typedef void (*ScriptCallBack)(void *, int);

typedef struct ScriptClass {
    int thread;
    char pad4[0x1C];
    int priority;
    int entry;
    unsigned char state; /* 0 not started, 1 running, 2 finished */
    unsigned char flags;
    char pad2A[2];
    int parent;
    int group;
    int work; /* freed with iosFree */
    int reset;
    int *env;
    int w40;
    int w44;
    int w48;
    ScriptCallBack finish;
    int finishArg;
    ScriptCallBack del;
    int delArg;
    ScriptCallBack del2;
    int del2Arg;
} ScriptClass;

typedef struct ScriptParam {
    int func;
    int arg4;
    int arg8;
    int priority;
    int parent;
    int flag14;
    int w18;
    int w1C;
    int w20;
} ScriptParam;

extern int execScriptGroup[];
extern void D_00087920(void);

extern void *GetScriptLayoutClass(void *);
extern void *GetScriptCharacterClass(void *);
extern void *GetWindowClass(void *);
extern void *GetScriptAnimationClass(void *);
extern void *GetScriptSpriteClass(void *);
extern void *GetScriptSpriteMenuClass(void *);
extern void isysInitSubThreadObj(void *, int, int, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
extern void isysInitGroup(void *);
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void isysInitSubThreadExecEnv(void *, int);
extern int isysWakeupSubThread(void *);
extern int isysStartSubThread(void *, int);
extern void isysLetterObjDiscardLetterAll(void *);
extern void isysRequestDeleteObj(void *);
extern void isysDeleteGroupAllObj(void *);
extern int isysGetSubThreadWorkSize(int);
extern int *_isysCreateObj(void *, int, int, int, void *, int);
extern void isysSetObjImmediateDeleteFunc(void *, void *);
extern void isysInitISYSLetterObj(void *);
extern void isysFlushISYSLetterObj(void *);
extern void isysDeleteSubThread(void *);
extern void iosFree(void *);
extern void *memset(void *, int, unsigned int);

static void func_000878B0(char *o);

void *GetScriptClass(void *obj)
{
    unsigned char *object = obj;

    switch (object[8]) {
    case 11: return GetScriptLayoutClass(object);
    case 9: return GetScriptCharacterClass(object);
    case 12: return GetWindowClass(object);
    case 13: return GetScriptAnimationClass(object);
    case 14: return GetScriptSpriteClass(object);
    case 33: return GetScriptSpriteMenuClass(object);
    case 6:
    case 22:
    case 29: return object + 0x20;
    case 32: return object + 0x1C;
    default: return 0;
    }
}

void initScriptObj(void *obj, ScriptParam *p, int stack)
{
    int a4;
    int priority = p->priority;
    ScriptClass *c = GetScriptClass(obj);

    if (p->func != 0) {
        isysInitSubThreadObj(obj, p->func, stack, p->arg8);
        a4 = p->arg4;
        ((ScriptClass *)GetScriptClass(obj))->entry = a4;
        c->priority = priority;
        c->state = 0;
        c->flags = p->flag14;
        isysAddGroupWithLinkParam(obj, &execScriptGroup[priority], 0, 0);
    } else {
        c->thread = 0;
    }
    c->work = 0;
    c->reset = 0;
    c->env = 0;
    if (p->parent != 0)
        isysAddGroupWithLinkParam(obj, &((ScriptClass *)GetScriptClass((void *)p->parent))->group, 0, 0);
    c->parent = p->parent;
    isysInitGroup(&c->group);
    c->w40 = p->w18;
    c->w44 = p->w1C;
    c->w48 = p->w20;
    { ScriptClass *t = GetScriptClass(obj); t->del = 0; t->delArg = 0; }
    { ScriptClass *t = GetScriptClass(obj); t->del2 = 0; t->del2Arg = 0; }
    { ScriptClass *t = GetScriptClass(obj); t->finish = 0; t->finishArg = 0; }
}

/* Runs one frame of every script in a priority group. */
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
            if (c->finish != 0)
                c->finish(obj, c->finishArg);
            c->state = 2;
            if (!(c->flags & 1))
                isysRequestDeleteObj(obj);
        }
    }
    if (obj != 0)
        isysGroupForExit(obj, 0);
}

void initScriptSystem(void)
{
    int i;
    int *g = execScriptGroup;
    for (i = 15; i >= 0; i--)
        isysInitGroup(g++);
}

int *createScriptObj(int script, int param, void *parent, int thread, int workSize,
                     int arg0, int arg1, int arg2)
{
    ScriptParam info;
    int *obj;

    obj = _isysCreateObj(parent, 6, 0x90, workSize + isysGetSubThreadWorkSize(thread) + 0x33,
                         func_000878B0, 4);
    isysSetObjImmediateDeleteFunc(obj, D_00087920);
    isysInitISYSLetterObj(obj);
    memset(&info, 0, sizeof(info));
    info.func = script;
    info.arg4 = param;
    info.arg8 = thread;
    info.priority = arg0;
    info.parent = arg1;
    info.flag14 = arg2;
    initScriptObj(obj, &info, *obj);
    return obj;
}

void flushScriptObj(void *obj)
{
    int work;
    ScriptClass *c;

    c = GetScriptClass(obj);
    work = c->work;
    if (work != 0) {
        iosFree((void *)work);
    }
    if (c->thread != 0) {
        isysDeleteSubThread(obj);
    }
}

void execScript(void)
{
    int i;
    int *g = execScriptGroup;
    for (i = 15; i >= 0; i--)
        func_000873A8(g++);
}

void flushScriptObjImmediate(void *obj)
{
    ScriptClass *s = GetScriptClass(obj);
    void *object;
    void **entry;

    if (s->del) {
        s->del(obj, s->delArg);
    }
    if (s->del2) {
        s->del2(obj, s->del2Arg);
    }
    object = 0;
    for (entry = isysGroupForFirst(&s->group, 0); entry != 0;
         entry = isysGroupForNext(entry, 0)) {
        object = *entry;
        isysRequestDeleteObj(object);
    }
    if (object != 0)
        isysGroupForExit(object, 0);
    isysDeleteGroupAllObj(&s->group);
}

int GetScriptObjWorkSize(int *p)
{
    return isysGetSubThreadWorkSize(p[2]);
}

void SetScriptObjDeleteCallBackFunc(void *actor, ScriptCallBack func, int arg)
{
    ScriptClass *s = GetScriptClass(actor);
    s->del = func;
    s->delArg = arg;
}

void SetScriptObjDeleteCallBackFunc2(void *actor, ScriptCallBack func, int arg)
{
    ScriptClass *s = GetScriptClass(actor);
    s->del2 = func;
    s->del2Arg = arg;
}

void SetScriptObjFinishCallBackFunc(void *actor, ScriptCallBack func, int arg)
{
    ScriptClass *s = GetScriptClass(actor);
    s->finish = func;
    s->finishArg = arg;
}

int *GetScriptPriorityGroup(int priority)
{
    return &execScriptGroup[priority];
}

void setScriptObjArgument(void *object, int argument)
{
    ((ScriptClass *)GetScriptClass(object))->entry = argument;
}

/* Delete function of a script object. */
static void func_000878B0(char *o)
{
    ScriptClass *s;

    if (*(int *)(o + 0x60) != 0) {
        *(int *)(o + 0x60) = 0;
    }
    s = GetScriptClass(o);
    if (s->work != 0) {
        iosFree((void *)s->work);
    }
    if (s->thread != 0) {
        isysDeleteSubThread(o);
    }
    isysFlushISYSLetterObj(o);
}
