extern void *GetScriptLayoutClass(unsigned char *);
extern char *GetScriptCharacterClass(unsigned char *);
extern char *GetWindowClass(unsigned char *);
extern char *GetScriptAnimationClass(unsigned char *);
extern char *GetScriptSpriteClass(unsigned char *);
extern char *GetScriptSpriteMenuClass(unsigned char *);
void *GetScriptClass(unsigned char *object)
{
    switch (object[8]) {
    case 11: return GetScriptLayoutClass(object);
    case 9: return GetScriptCharacterClass(object);
    case 12: return GetWindowClass(object);
    case 13: return GetScriptAnimationClass(object);
    case 14: return GetScriptSpriteClass(object);
    case 33: return GetScriptSpriteMenuClass(object);
    case 6:
    case 22:
    case 29: return object + 0x20;
    case 32: return object + 0x1C;
    default: return 0;
    }
}

