extern int GetLayoutObjWorkSize(void *);
extern int GetScriptObjWorkSize(int *);
extern void *_isysCreateObj(void *, int, int, int, int, int);
extern void isysInitISYSLetterObj(void *);
extern int InitLayoutObj(unsigned char *, int *);
extern void initScriptObj(void *, void *, int);
extern char *GetScriptAnimationClass(unsigned char *);
extern void InitDamageClass(char *);
extern void isysSetObjImmediateDeleteFunc(void *, int);
extern int InitAliasLayoutObj(unsigned char *, int *, unsigned char *);
extern int FlushLayoutObj(unsigned char *);
extern void flushScriptObj(int);
extern void iosFree(int);
extern void *GetDamageClass(void *);
extern void ResetDamageClass(void *);
extern void CheckDamageLetter(void *, void *);
extern void CheckLetter(void *, void (*)(void *, void *));
extern void FlushLayoutObjImmediate(void *obj);
extern void flushScriptObjImmediate(void *obj);
typedef struct {
    char pad0[0x2D4];
    void *buf;
} ScriptLayoutClass;
extern void isysFlushISYSLetterObj(void *);

void *GetScriptLayoutClass(unsigned char *o);
static void func_00091FC0(void *obj);
static void T_00092010(void *obj);

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

unsigned char *CreateAliasScriptLayoutObj(void *heap, int extra, int *def, unsigned char *parent)
{
    int *script = def + 31;
    int layoutWork = GetLayoutObjWorkSize(def);
    int scriptWork = GetScriptObjWorkSize(script);
    unsigned char *obj = _isysCreateObj(heap, 11, 0x300, extra + (layoutWork + scriptWork), (int)func_00091FC0, 16);
    if (obj) {
        unsigned char *cls;
        unsigned char *other;
        isysInitISYSLetterObj(obj);
        InitAliasLayoutObj(obj, def, parent);
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

void FlushScriptLayoutObj(unsigned char *object)
{
    int allocation;

    FlushLayoutObj(object);
    flushScriptObj((int)object);
    allocation = *(int *)((char *)GetScriptLayoutClass(object) + 0x2D4);
    if (allocation != 0) {
        iosFree(allocation);
    }
}

void *GetScriptLayoutClass(unsigned char *o)
{
    switch (o[8]) {
    case 0xB:
        return o + 0x20;
    case 0xD:
        return GetScriptAnimationClass(o);
    }
    return 0;
}

void SetScriptLayoutObjLetterProcMode(unsigned char *p, int mode)
{
    char *c;
    if (p[8] == 0xB)
        c = (char *)p + 0x20;
    else if (p[8] == 0xD)
        c = GetScriptAnimationClass(p);
    else
        c = 0;
    *(int *)(c + 0x2D0) = mode;
}

void ExecScriptLayoutObj(void *object)
{
    ResetDamageClass(GetDamageClass(object));
    CheckLetter(object, CheckDamageLetter);
}

int InitScriptLayoutObj(unsigned char *obj, int *def)
{
    unsigned char *cls;
    unsigned char *other;
    InitLayoutObj(obj, def);
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

int GetScriptLayoutObjWorkSize(int arg0)
{
    int temp_s1;

    temp_s1 = GetLayoutObjWorkSize((void *)arg0);
    return temp_s1 + GetScriptObjWorkSize(arg0 + 0x7C);
}

void FlushScriptLayoutObjImmediate(void *obj)
{
    FlushLayoutObjImmediate(obj);
    flushScriptObjImmediate(obj);
}

static void func_00091FC0(void *obj)
{
    ScriptLayoutClass *c;

    FlushLayoutObj(obj);
    flushScriptObj(obj);
    c = GetScriptLayoutClass(obj);
    if (c->buf)
        iosFree(c->buf);
    isysFlushISYSLetterObj(obj);
}

static void T_00092010(void *obj)
{
    FlushLayoutObjImmediate(obj);
    flushScriptObjImmediate(obj);
}
