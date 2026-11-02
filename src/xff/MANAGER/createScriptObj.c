typedef struct ScriptInfo {
    int script;
    int param;
    int thread;
    int arg0;
    int arg1;
    int arg2;
    char pad18[0xC];
} ScriptInfo;

extern int isysGetSubThreadWorkSize(int);
extern int *_isysCreateObj(void *, int, int, int, void *, int);
extern void isysSetObjImmediateDeleteFunc(void *, void *);
extern void isysInitISYSLetterObj(void *);
extern void *memset(void *, int, unsigned int);
extern void initScriptObj(void *, ScriptInfo *, int);
extern void func_000878B0(void);
extern void D_00087920(void);

int *createScriptObj(int script, int param, void *parent, int thread, int workSize,
                     int arg0, int arg1, int arg2)
{
    ScriptInfo info;
    int *obj;

    obj = _isysCreateObj(parent, 6, 0x90, workSize + isysGetSubThreadWorkSize(thread) + 0x33,
                         func_000878B0, 4);
    isysSetObjImmediateDeleteFunc(obj, D_00087920);
    isysInitISYSLetterObj(obj);
    memset(&info, 0, sizeof(info));
    info.script = script;
    info.param = param;
    info.thread = thread;
    info.arg0 = arg0;
    info.arg1 = arg1;
    info.arg2 = arg2;
    initScriptObj(obj, &info, *obj);
    return obj;
}
