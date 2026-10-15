extern void flushScriptObj(unsigned char *);

void DeleteScriptSpriteObj(unsigned char *o)
{
    unsigned char *c = o[8] != 0xE ? 0 : o + 0x90;
    unsigned char *d = o[8] != 0xE ? 0 : o + 0x20;
    *(int *)(c + 0x4C) = 0;
    if (*(int *)(c + 0x50) == 0)
        *(int *)(c + 0x50) = 1;
    flushScriptObj(o);
    if (*(void (**)(unsigned char *))(d + 0xCC) != 0)
        (*(void (**)(unsigned char *))(d + 0xCC))(o);
}
