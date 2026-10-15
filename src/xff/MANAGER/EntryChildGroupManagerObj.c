extern char *GetScriptAnimationClass(unsigned char *);
extern char *GetScrLwsOriClass(unsigned char *);
extern void ScanAllTwoWayLink(void *, void *, char *);

void EntryChildGroupManagerObj(unsigned char *o, void *b, void *c)
{
    char *m;
    switch (o[8]) {
    case 0xD:
        m = GetScriptAnimationClass(o) + 0x320;
        break;
    case 0x16:
        m = GetScrLwsOriClass(o) + 0x11F0;
        break;
    default:
        m = 0;
        break;
    }
    *m = 1;
    ScanAllTwoWayLink(b, c, m + 2);
}
