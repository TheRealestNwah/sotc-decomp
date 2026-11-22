typedef struct {
    void *obj;
} SysGroup;

typedef struct {
    char pad0[0x10];
    unsigned int ref;
    unsigned int max : 4;
    unsigned int cnt : 4;
} AnimDef;

typedef struct {
    char pad0[0xAC];
    AnimDef *def;
} ScriptDef;

typedef struct {
    char pad0[0xC];
    void *group;
} Info;

extern int DldSysUndefSymbol;
extern Info info;
extern int GetScriptLayoutObjWorkSize(ScriptDef *);
extern int GetJudgeVolumeClassWorkSize(unsigned int *);
extern void *initAnimDefSegOneElement(AnimDef *);
extern int *GetAnimationDefClass(void *);
extern unsigned char *_isysCreateObj(void *, int, int, int, int, int);
extern void isysInitISYSLetterObj(unsigned char *);
extern void isysSetObjImmediateDeleteFunc(unsigned char *, int);
extern SysGroup *isysGroupForFirst(void *, int);
extern SysGroup *isysGroupForNext(SysGroup *, int);
extern void isysGroupForExit(void *, int);
extern void isysRequestDeleteObj(void *);
extern void InitScriptLayoutObj(unsigned char *, ScriptDef *);
extern void InitChildGroupManagerObj(unsigned char *);
extern char *GetLayoutClass(unsigned char *);
extern void func_0008A6A8(ScriptDef *, unsigned char *, void *);
extern void func_00088678(unsigned char *, int);
extern int D_00091038();
extern void D_00091098();

static inline int dldEntry(unsigned int *h)
{
    unsigned int enc = *h;
    unsigned int off = enc & 0x3FFFF;
    int *o = off ? *(int **)((char *)h - off) : 0;
    if (o != 0 && o != (int *)DldSysUndefSymbol)
        return o[4] + ((enc >> 18) & 0xFFF) * *(int *)(o[2] + 0xC);
    return 0;
}

unsigned char *CreateScriptAnimationObj(void *heap, int extra, ScriptDef *sd)
{
    unsigned char *obj;
    int size = GetScriptLayoutObjWorkSize(sd);
    unsigned int *ref = &sd->def->ref;

    if (dldEntry(ref) != 0)
        size = size + GetJudgeVolumeClassWorkSize(ref) + 0x3F;
    size = size + *GetAnimationDefClass(initAnimDefSegOneElement(sd->def)) * 8 + 0x33;
    obj = _isysCreateObj(heap, 0xD, 0x390, extra + size, (int)D_00091038, 0x10);
    if (obj == 0)
        return 0;
    {
        AnimDef *d;
        isysInitISYSLetterObj(obj);
        isysSetObjImmediateDeleteFunc(obj, (int)D_00091098);
        d = sd->def;
        if (d->max != 0) {
            if (d->max == d->cnt) {
                unsigned int newest = 0;
                register int type __asm__("$22");
                void *oldest = 0;
                void *last = 0;
                SysGroup *g;
                g = isysGroupForFirst(info.group, 0);
                if (g != 0) {
                    type = 0xD;
                    do {
                    unsigned char *cls;
                    last = g->obj;
                    cls = ((unsigned char *)last)[8] != type ? 0 : (unsigned char *)last + 0x20;
                    if (*(AnimDef **)(cls + 0x32C) == d && *(unsigned int *)(cls + 0x340) >= newest) {
                        newest = *(unsigned int *)(cls + 0x340);
                        oldest = last;
                    }
                    } while ((g = isysGroupForNext(g, 0)) != 0);
                }
                if (last != 0)
                    isysGroupForExit(last, 0);
                isysRequestDeleteObj(oldest);
            }
            d->cnt++;
        }
        InitScriptLayoutObj(obj, sd);
        InitChildGroupManagerObj(obj);
        func_0008A6A8(sd, obj, heap);
        func_00088678(obj, *(signed char *)(GetLayoutClass(obj) + 0x1B8));
    }
    return obj;
}
