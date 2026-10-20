extern int GetScriptObjWorkSize(int *);
extern void *_isysCreateObj(void *, int, int, int, int, int);
extern void DeleteScriptSpriteObj(unsigned char *);
static int func_000991E8(int, int, int, int);
extern void isysSetObjImmediateDeleteFunc(void *, int);
static int InitSpriteObj(unsigned char *, int *);
extern void initScriptObj(void *, void *, int);

unsigned char *CreateScriptSpriteObj(void *heap, int extra, int *def)
{
    int *script = def + 15;
    int work = def[2] * 135;
    int scriptWork = GetScriptObjWorkSize(script);
    unsigned char *obj;
    work += 0x43;
    work += scriptWork;
    obj = _isysCreateObj(heap, 14, 0xF0, extra + work, (int)DeleteScriptSpriteObj, 16);
    if (obj) {
        unsigned char *cls;
        isysSetObjImmediateDeleteFunc(obj, (int)func_000991E8);
        InitSpriteObj(obj, def);
        initScriptObj(obj, script, *(int *)obj);
        cls = obj[8] != 14 ? 0 : obj + 0x20;
        *(int *)(cls + 0xCC) = def[14];
    }
    return obj;
}