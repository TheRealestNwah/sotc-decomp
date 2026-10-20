extern int GetScriptObjWorkSize(int *);
extern void *_isysCreateObj(void *, int, int, int, int, int);
extern void DeleteScriptSpriteMenuObj(unsigned char *);
static int func_00098A70(unsigned char *);
extern void isysSetObjImmediateDeleteFunc(void *, int);
static void func_00096070(unsigned char *, int *);
static int func_00096530(int *);
extern void initScriptObj(void *, void *, int);

unsigned char *CreateScriptSpriteMenuObj(void *heap, int extra, int *def)
{
    int *script = def + 11;
    int work = func_00096530(def);
    int scriptWork = GetScriptObjWorkSize(script);
    unsigned char *obj = _isysCreateObj(heap, 33, 0xD0, extra + work + scriptWork, (int)DeleteScriptSpriteMenuObj, 16);
    if (obj) {
        unsigned char *cls;
        isysSetObjImmediateDeleteFunc(obj, (int)func_00098A70);
        initScriptObj(obj, script, *(int *)obj);
        func_00096070(obj, def);
        cls = obj[8] != 33 ? 0 : obj + 0x20;
        *(int *)(cls + 0xA0) = def[10];
    }
    return obj;
}