typedef struct Ptn Ptn;
extern Ptn rootPtn;
static void func_0000E058(void);
static void func_0000DFF8(void);
extern void *createScriptObj(void *, int, Ptn *, int, int, int, int, int);
extern void SetScriptObjDeleteCallBackFunc(void *, void *, int);

void *fsEffectCreateSetScript(int a, int b, int c)
{
    void *o = createScriptObj(func_0000E058, c, &rootPtn, 0x1800, 0, 8, b, 0);
    if (o != 0)
        SetScriptObjDeleteCallBackFunc(o, func_0000DFF8, c);
    return o;
}
