extern char *GetScriptClass(void *);
extern void iosFree(void *);
extern void isysDeleteSubThread(void *);
extern void isysFlushISYSLetterObj(void *);

static void func_000878B0(char *o)
{
    char *s;

    if (*(int *)(o + 0x60) != 0) {
        *(int *)(o + 0x60) = 0;
    }
    s = GetScriptClass(o);
    if (*(void **)(s + 0x34) != 0) {
        iosFree(*(void **)(s + 0x34));
    }
    if (*(int *)s != 0) {
        isysDeleteSubThread(o);
    }
    isysFlushISYSLetterObj(o);
}
