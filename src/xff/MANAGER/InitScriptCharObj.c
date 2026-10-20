extern long iosGetTCount(void);
extern float iosGetSecondFromTCount(unsigned long);
extern int InitCharacterObj(unsigned char *, int *);
extern void initScriptObj(void *, void *, int);
void InitScriptCharObj(unsigned char *obj, int *def)
{
    long start = iosGetTCount();
    unsigned char *cls;
    InitCharacterObj(obj, def);
    iosGetSecondFromTCount((unsigned long)(iosGetTCount() - start));
    initScriptObj(obj, def + 71, *(int *)obj);
    iosGetSecondFromTCount((unsigned long)(iosGetTCount() - start));
    cls = obj[8] != 9 ? 0 : obj + 0x20;
    *(int *)(cls + 0x11F0) = def[80];
    *(int *)(cls + 0x11F4) = def[81];
    *(int *)(cls + 0x11F8) = def[82];
    *(int *)(cls + 0x1204) = 0;
    *(int *)(cls + 0x1200) = 0;
    *(int *)(cls + 0x11FC) = 0;
    *(int *)(cls + 0x1208) = 0;
    *(int *)(cls + 0x120C) = 0;
}