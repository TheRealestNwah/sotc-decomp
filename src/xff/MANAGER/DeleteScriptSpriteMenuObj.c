extern void flushScriptObj(unsigned char *);

void DeleteScriptSpriteMenuObj(unsigned char *p)
{
    unsigned char *m = p[8] != 0x21 ? 0 : p + 0x20;
    void (*f)(unsigned char *);
    flushScriptObj(p);
    f = *(void (**)(unsigned char *))(m + 0xA0);
    if (f != 0)
        f(p);
}
