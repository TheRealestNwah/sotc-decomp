extern void flushScriptObj(void *);
extern void FlushCharacterObj(void *);
extern void iosFree(void *);
extern void isysFlushISYSLetterObj(void *);

static void T_00091A60(char *o)
{
    char *w = *(unsigned char *)(o + 8) == 9 ? o + 0x20 : 0;

    flushScriptObj(o);
    FlushCharacterObj(o);
    if (*(void **)(w + 0x11FC))
        iosFree(*(void **)(w + 0x11FC));
    isysFlushISYSLetterObj(o);
}
