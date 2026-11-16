/* Flushes a LWS demo orient manager object's script, then its letter object. */
extern void flushScriptObj(void *);
extern void isysFlushISYSLetterObj(void *);

static void T_0007E978(void *o)
{
    flushScriptObj(o);
    isysFlushISYSLetterObj(o);
}
