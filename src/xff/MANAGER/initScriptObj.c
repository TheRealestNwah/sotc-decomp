typedef struct ScriptClass {
    int w0;
    char pad4[0x1C];
    int priority;
    int arg24;
    unsigned char state;
    unsigned char flag29;
    char pad2A[2];
    int parent;
    int group30;
    int w34;
    int w38;
    int w3C;
    int w40;
    int w44;
    int w48;
    int w4C;
    int w50;
    int w54;
    int w58;
    int w5C;
    int w60;
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
extern ScriptClass *GetScriptClass(int);
extern void isysInitSubThreadObj(int, int, int, int);
extern void isysAddGroupWithLinkParam(int, void *, int, int);
extern void isysInitGroup(void *);

void initScriptObj(int obj, ScriptParam *p, int stack)
{
    int a4;
    int priority = p->priority;
    ScriptClass *c = GetScriptClass(obj);

    if (p->func != 0) {
        isysInitSubThreadObj(obj, p->func, stack, p->arg8);
        a4 = p->arg4;
        GetScriptClass(obj)->arg24 = a4;
        c->priority = priority;
        c->state = 0;
        c->flag29 = p->flag14;
        isysAddGroupWithLinkParam(obj, &execScriptGroup[priority], 0, 0);
    } else {
        c->w0 = 0;
    }
    c->w34 = 0;
    c->w38 = 0;
    c->w3C = 0;
    if (p->parent != 0)
        isysAddGroupWithLinkParam(obj, &GetScriptClass(p->parent)->group30, 0, 0);
    c->parent = p->parent;
    isysInitGroup(&c->group30);
    c->w40 = p->w18;
    c->w44 = p->w1C;
    c->w48 = p->w20;
    { ScriptClass *t = GetScriptClass(obj); t->w54 = 0; t->w58 = 0; }
    { ScriptClass *t = GetScriptClass(obj); t->w5C = 0; t->w60 = 0; }
    { ScriptClass *t = GetScriptClass(obj); t->w4C = 0; t->w50 = 0; }
}
