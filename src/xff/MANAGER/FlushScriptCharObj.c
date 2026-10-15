extern void flushScriptObj(unsigned char *);
extern void FlushCharacterObj(unsigned char *);
extern void iosFree(void *);

void FlushScriptCharObj(unsigned char *p)
{
    unsigned char *c = p[8] != 9 ? 0 : p + 0x20;
    void *w;
    flushScriptObj(p);
    FlushCharacterObj(p);
    w = *(void **)(c + 0x11FC);
    if (w != 0)
        iosFree(w);
}
