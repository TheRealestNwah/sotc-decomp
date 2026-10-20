extern int GetLwsOrientWorkSize(void *);
extern int GetScriptObjWorkSize(int *);
extern void *_isysCreateObj(void *, int, int, int, int, int);
static void func_00092820(unsigned char *);
static void func_000920F0(unsigned char *);
extern void isysSetObjImmediateDeleteFunc(void *, int);
extern void isysInitISYSLetterObj(void *);
extern int InitLwsOrientObj(unsigned char *, int *);
extern void initScriptObj(void *, void *, int);
extern void InitChildGroupManagerObj(unsigned char *);
extern int isysAddGroupWithLinkParam(void *, void *, int, int);
unsigned char *CreateScriptLwsOri(void *heap, int extra, int *def)
{
    int *script = def + 77;
    int orientWork = GetLwsOrientWorkSize(def);
    int scriptWork = GetScriptObjWorkSize(script);
    unsigned char *obj = _isysCreateObj(heap, 22, 0x1250, extra + (orientWork + scriptWork), (int)func_00092820, 16);
    if (obj) {
        unsigned char *cls;
        int *buffer;
        int *cb;
        isysSetObjImmediateDeleteFunc(obj, (int)func_000920F0);
        isysInitISYSLetterObj(obj);
        InitLwsOrientObj(obj, def);
        initScriptObj(obj, script, *(int *)obj);
        InitChildGroupManagerObj(obj);
        cls = obj[8] != 22 ? 0 : obj + 0x20;
        buffer = (int *)(cls + 0x1204);
        cb = (int *)(cls + 0x120C);
        buffer[1] = 0;
        buffer[0] = 0;
        *(int *)(cls + 0x1214) = 0;
        cb[0] = 0;
        cb[1] = 0;
        isysAddGroupWithLinkParam(obj, (void *)def[72], 0, 0);
    }
    return obj;
}