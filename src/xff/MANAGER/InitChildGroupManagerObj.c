extern char *GetScriptAnimationClass(unsigned char *);
extern char *GetScrLwsOriClass(unsigned char *);
extern void isysInitGroup(char *);

void InitChildGroupManagerObj(unsigned char *p)
{
    char *g;
    switch (p[8]) {
    case 0xD:
        g = GetScriptAnimationClass(p) + 0x320;
        break;
    case 0x16:
        g = GetScrLwsOriClass(p) + 0x11F0;
        break;
    default:
        g = 0;
        break;
    }
    g[0] = 0;
    isysInitGroup(g + 2);
}
