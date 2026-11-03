extern void *DldSysUndefSymbol;
extern char _AnimObjDef[];
extern char _BlendMotionDef[];

typedef struct {
    short pad0[2];
    short count;
    short pad6;
    char pad8[0x14];
    char *table;
} AnimObjResource;

extern AnimObjResource *getAnimObjResource(unsigned int *);
extern unsigned int *getBlendLastMotion(unsigned int *);
extern void func_00032E98(int, int, int, char *, int, float);

static inline char *resourceModule(unsigned int *reference)
{
    unsigned int offset = *reference & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != DldSysUndefSymbol)
        return module;
    return 0;
}

int GetMotionOptionNodeFloatFrame(int a, int b, int c, unsigned int *obj, int index, float frame)
{
top:
    if (*(char **)(resourceModule(obj) + 8) == _AnimObjDef) {
        AnimObjResource *r = getAnimObjResource(obj);
        func_00032E98(a, b, c, r->table + index * 16, r->count, frame);
    } else if (*(char **)(resourceModule(obj) + 8) == _BlendMotionDef) {
        obj = getBlendLastMotion(obj);
        goto top;
    }
}
