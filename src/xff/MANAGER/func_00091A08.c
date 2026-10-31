extern void flushScriptObjImmediate(void *);
extern void FlushCharacterObjImmediate(void *);

typedef struct {
    void (*func)(int);
    int arg;
} Callback;

typedef struct {
    char p0[0x1208];
    Callback cb;
} Work;

typedef struct {
    int p0;
    int p4;
    unsigned char type;
    char p9[0x17];
    Work work;
} Obj;

static void func_00091A08(Obj *o)
{
    Work *w = o->type == 9 ? &o->work : 0;


    if (w->cb.func != 0) {
        w->cb.func(w->cb.arg);
    }
    flushScriptObjImmediate(o);
    FlushCharacterObjImmediate(o);
}
