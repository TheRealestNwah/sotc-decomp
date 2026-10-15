extern char *GetScriptAnimationClass(unsigned char *);
extern char *GetScrLwsOriClass(unsigned char *);
extern void isysDeleteGroupAllObj(char *);

void FlushChildGroupManagerObj(unsigned char *p)
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
    isysDeleteGroupAllObj(g + 2);
    g[0] = 0;
}
