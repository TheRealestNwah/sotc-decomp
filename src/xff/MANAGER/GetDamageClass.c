extern char *GetCharacterClass(void *);
extern char *GetScriptLayoutClass(void *);
extern char *GetScriptAnimationClass(void *);

char *GetDamageClass(char *o)
{
    switch (((unsigned char *)o)[8]) {
    case 9:
        return GetCharacterClass(o) + 0x200;
    case 0xB:
        return GetScriptLayoutClass(o) + 0x230;
    case 0xD:
        return GetScriptAnimationClass(o) + 0x230;
    case 0x16:
        return o + 0x290;
    }
    return 0;
}
