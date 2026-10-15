extern char *GetCharacterClass(unsigned char *);
extern char *GetScriptAnimationClass(unsigned char *);

char *GetAnimationClass(unsigned char *o)
{
    switch (o[8]) {
    case 9:
        return GetCharacterClass(o) + 0x1C0;
    case 0xD:
        return GetScriptAnimationClass(o) + 0x2E0;
    case 0x16:
        return (char *)o + 0x250;
    }
    return 0;
}
