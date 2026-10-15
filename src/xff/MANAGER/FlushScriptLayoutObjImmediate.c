extern void FlushLayoutObjImmediate(void *obj);
extern void flushScriptObjImmediate(void *obj);

void FlushScriptLayoutObjImmediate(void *obj)
{
    FlushLayoutObjImmediate(obj);
    flushScriptObjImmediate(obj);
}
