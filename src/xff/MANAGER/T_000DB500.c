extern void windowDelete(int);
extern void flushScriptObjImmediate(void *);

static void T_000DB500(char *o)
{
    windowDelete(*(int *)(o + 0xB4));
    flushScriptObjImmediate(o);
}
