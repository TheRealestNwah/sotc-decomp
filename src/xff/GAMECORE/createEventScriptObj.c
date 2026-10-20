typedef struct {
    char pad0[0x10];
    int x10;
} ScriptDesc;

extern ScriptDesc D_0017B8D0;
extern char D_0012AE40[];
extern void func_0012AE28(void);
extern int GetScriptObjWorkSize(void *);
extern void *_isysCreateObj(void *, int, int, int, int, int);
extern void isysSetObjImmediateDeleteFunc(void *, void (*)(void));
extern void initScriptObj(void *, void *, int);

static inline ScriptDesc *setupDesc(int *desc)
{
    D_0017B8D0.x10 = desc[0];
    return &D_0017B8D0;
}

unsigned char *createEventScriptObj(void *parent, int extra, int *desc)
{
    unsigned char *o;
    char *c;
    int w;

    o = _isysCreateObj(parent, 0x20, 0xA0, extra + GetScriptObjWorkSize(setupDesc(desc)) + 0x33, (int)D_0012AE40, 4);
    isysSetObjImmediateDeleteFunc(o, func_0012AE28);
    w = *(int *)o;
    initScriptObj(o, setupDesc(desc), w);
    c = o[8] == 0x20 ? (char *)o + 0x20 : 0;
    *(int *)(c + 0x70) = desc[1];
    *(int *)(c + 0x74) = desc[2];
    return o;
}
