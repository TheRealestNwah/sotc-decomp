extern void *GetScriptAnimationClass(void *);

void *GetScriptLayoutClass(unsigned char *o)
{
    switch (o[8]) {
    case 0xB:
        return o + 0x20;
    case 0xD:
        return GetScriptAnimationClass(o);
    }
    return 0;
}
