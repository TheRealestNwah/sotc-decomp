typedef struct {
    char pad0[0x2D4];
    void *buf;
} ScriptLayoutClass;

extern void FlushLayoutObj(void *);
extern void flushScriptObj(void *);
extern ScriptLayoutClass *GetScriptLayoutClass(void *);
extern void iosFree(void *);
extern void isysFlushISYSLetterObj(void *);
extern void FlushLayoutObjImmediate(void *);
extern void flushScriptObjImmediate(void *);

static void func_00091FC0(void *obj)
{
    ScriptLayoutClass *c;

    FlushLayoutObj(obj);
    flushScriptObj(obj);
    c = GetScriptLayoutClass(obj);
    if (c->buf)
        iosFree(c->buf);
    isysFlushISYSLetterObj(obj);
}

static void T_00092010(void *obj)
{
    FlushLayoutObjImmediate(obj);
    flushScriptObjImmediate(obj);
}
