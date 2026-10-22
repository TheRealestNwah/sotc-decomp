extern char *GetScriptAnimationClass(unsigned char *);
extern char *GetScrLwsOriClass(unsigned char *);

char *GetChildGroupManagerClass(unsigned char *object)
{
    switch (object[8]) {
    case 13:
        return GetScriptAnimationClass(object) + 0x320;
    case 22:
        return GetScrLwsOriClass(object) + 0x11F0;
    default:
        return 0;
    }
}
