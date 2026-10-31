extern void flushScriptObj(void *);
extern void FlushCharacterObj(void *);
extern void FlushChildGroupManagerObj(void *);
extern void iosFree(void *);
extern void isysFlushISYSLetterObj(void *);

typedef struct {
    void (*func)(int);
    int arg;
} Callback;

typedef struct {
    char p0[0x1204];
    void *buf;
    int p1208;
    Callback cb;
} Work;

typedef struct {
    int p0;
    int p4;
    unsigned char type;
    char p9[0x17];
    Work work;
} Obj;

static void func_00092820(Obj *o)
{
    Work *w = o->type == 0x16 ? &o->work : 0;
    Callback *cb = &w->cb;

    if (cb->func != 0) {
        cb->func(cb->arg);
    }
    flushScriptObj(o);
    FlushCharacterObj(o);
    FlushChildGroupManagerObj(o);
    if (w->buf != 0) {
        iosFree(w->buf);
    }
    isysFlushISYSLetterObj(o);
}
