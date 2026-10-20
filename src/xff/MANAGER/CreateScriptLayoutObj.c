extern int GetLayoutObjWorkSize(void *);
extern int GetScriptObjWorkSize(int *);
extern void *_isysCreateObj(void *, int, int, int, int, int);
static void func_00091FC0(unsigned char *);
static int T_00092010(unsigned char *);
extern void isysInitISYSLetterObj(void *);
extern int InitLayoutObj(unsigned char *, int *);
extern void initScriptObj(void *, void *, int);
extern char *GetScriptAnimationClass(unsigned char *);
extern void InitDamageClass(char *);
extern void isysSetObjImmediateDeleteFunc(void *, int);
unsigned char *CreateScriptLayoutObj(void *heap, int extra, int *def)
{
    int *script = def + 31;
    int layoutWork = GetLayoutObjWorkSize(def);
    int scriptWork = GetScriptObjWorkSize(script);
    unsigned char *obj = _isysCreateObj(heap, 11, 0x300, extra + (layoutWork + scriptWork) + 0x33, (int)func_00091FC0, 16);
    if (obj) {
        unsigned char *cls;
        unsigned char *other;
        isysInitISYSLetterObj(obj);
        InitLayoutObj(obj, def);
        initScriptObj(obj, script, *(int *)obj);
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
        isysSetObjImmediateDeleteFunc(obj, (int)T_00092010);
    }
    return obj;
}