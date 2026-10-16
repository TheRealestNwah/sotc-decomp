typedef struct {
    void (*fn)(int);
    int arg;
} LwsCb;

extern void flushScriptObj(void *);
extern void FlushCharacterObj(void *);
extern void FlushChildGroupManagerObj(void *);
extern void iosFree(void *);

void FlushScriptLwsOri(unsigned char *o)
{
    unsigned char *c = o[8] != 0x16 ? 0 : o + 0x20;
    LwsCb *cb = (LwsCb *)(c + 0x120C);

    if (cb->fn != 0)
        cb->fn(cb->arg);
    flushScriptObj(o);
    FlushCharacterObj(o);
    FlushChildGroupManagerObj(o);
    if (*(void **)(c + 0x1204) != 0)
        iosFree(*(void **)(c + 0x1204));
}
