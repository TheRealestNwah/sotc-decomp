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
static int T_00091A60(unsigned char *);
static void func_00091A08(unsigned char *);

static inline void InitScriptCharObj(unsigned char *obj, int *def)
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
        InitScriptCharObj(obj, def);
        isysSetObjImmediateDeleteFunc(obj, (int)func_00091A08);
    }
    return obj;
}
