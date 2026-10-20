extern int InitAliasLayoutObj(unsigned char *, int *, unsigned char *);
extern void initScriptObj(void *, void *, int);
extern char *GetScriptAnimationClass(unsigned char *);
extern void InitDamageClass(char *);
int InitAliasScriptLayoutObj(unsigned char *obj, int *def, unsigned char *parent)
{
    unsigned char *cls;
    unsigned char *other;
    InitAliasLayoutObj(obj, def, parent);
    initScriptObj(obj, def + 31, *(int *)obj);
    switch (obj[8]) {
    case 11: cls = obj + 0x20; break;
    case 13: cls = (unsigned char *)GetScriptAnimationClass(obj); break;
    default: cls = 0;
    }
    *(int *)(cls + 0x2D4) = 0;
    *(int *)(cls + 0x2DC) = def[40];
    switch (obj[8]) {
    case 11: other = obj + 0x20; break;
    case 13: other = (unsigned char *)GetScriptAnimationClass(obj); break;
    default: other = 0;
    }
    *(int *)(other + 0x2D0) = 0;
    InitDamageClass((char *)cls + 0x230);
    return 1;
}
