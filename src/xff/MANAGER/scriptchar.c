extern int DldSysUndefSymbol;
extern int D_00136E70;
extern int GetCharacterObjWorkSize(int *);
extern int GetScriptObjWorkSize(int *);
extern void *_isysCreateObj(void *, int, int, int, int, int);
extern void isysSetObjImmediateDeleteFunc(void *, int);
extern void isysInitISYSLetterObj(void *);
extern long iosGetTCount(void);
extern float iosGetSecondFromTCount(unsigned long);
extern int InitCharacterObj(unsigned char *, int *);
extern void initScriptObj(void *, void *, int);
extern void flushScriptObj(unsigned char *);
extern void FlushCharacterObj(unsigned char *);
extern void iosFree(void *);
extern void flushScriptObjImmediate(void *);
extern void FlushCharacterObjImmediate(void *);
typedef struct {
    void (*func)(int);
    int arg;
} Callback;
typedef struct {
    char p0[0x1208];
    Callback cb;
} Work;
typedef struct {
    int p0;
    int p4;
    unsigned char type;
    char p9[0x17];
    Work work;
} Obj;
extern void isysFlushISYSLetterObj(void *);

void InitScriptCharObj(unsigned char *obj, int *def);
static void func_00091A08(Obj *o);
static void T_00091A60(char *o);

static inline void InitScriptCharObjInline(unsigned char *obj, int *def)
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

unsigned char *CreateScriptCharObj(void *heap, int extra, int *def)
{
    unsigned char *obj;
    extra = extra + (GetCharacterObjWorkSize(def) + GetScriptObjWorkSize(def + 71)) + 0x33;
    if (def[71] == DldSysUndefSymbol) {
        if (D_00136E70 == 0)
            return 0;
        def[71] = D_00136E70;
    }
    obj = _isysCreateObj(heap, 9, 0x1230, extra, (int)T_00091A60, 16);
    if (obj) {
        isysInitISYSLetterObj(obj);
        InitScriptCharObjInline(obj, def);
        isysSetObjImmediateDeleteFunc(obj, (int)func_00091A08);
    }
    return obj;
}

char *GetScriptCharacterClass(unsigned char *p)
{
    if (p[0x8] != 0x9) {
        return 0;
    }
    return (char *)p + 0x20;
}

void FlushScriptCharObj(unsigned char *p)
{
    unsigned char *c = p[8] != 9 ? 0 : p + 0x20;
    void *w;
    flushScriptObj(p);
    FlushCharacterObj(p);
    w = *(void **)(c + 0x11FC);
    if (w != 0)
        iosFree(w);
}


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

void SetScriptCharDefaultScriptFunc(int arg0)
{
    D_00136E70 = arg0;
}

void SetScriptCharacterObjReleaseCallBackFunc(unsigned char *p, int a, int b)
{
    char *c = p[8] != 9 ? 0 : (char *)p + 0x20;

    *(int *)(c + 0x1208) = a;
    *(int *)(c + 0x120C) = b;
}

static void func_00091A08(Obj *o)
{
    Work *w = o->type == 9 ? &o->work : 0;


    if (w->cb.func != 0) {
        w->cb.func(w->cb.arg);
    }
    flushScriptObjImmediate(o);
    FlushCharacterObjImmediate(o);
}

static void T_00091A60(char *o)
{
    char *w = *(unsigned char *)(o + 8) == 9 ? o + 0x20 : 0;

    flushScriptObj(o);
    FlushCharacterObj(o);
    if (*(void **)(w + 0x11FC))
        iosFree(*(void **)(w + 0x11FC));
    isysFlushISYSLetterObj(o);
}
