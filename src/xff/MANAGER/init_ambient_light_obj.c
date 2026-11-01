extern int *DldSysUndefSymbol;
extern char *D_00136C10;

typedef struct {
    int color;
    int unk4;
    int unk8;
} AmbientLightParam;

typedef struct {
    int unk0;
    unsigned int def;
    int unk8;
    int unkC;
} AmbientLightDesc;

extern void *CreateAmbientLightObj(void *, int, AmbientLightParam);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);

static inline int *dldObj(int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (int *)t[4] : 0;
}

void *initAmbientLightObj(void *parent, AmbientLightDesc *desc)
{
    int *def = dldObj((int *)&desc->def);
    AmbientLightParam param;
    AmbientLightParam tmp;
    void *obj;

    tmp.color = def[3];
    tmp.unk4 = desc->unk8;
    tmp.unk8 = desc->unkC;
    param = tmp;
    obj = CreateAmbientLightObj(parent, 0x10, param);
    if (obj) {
        isysAddGroupWithLinkParam(obj, D_00136C10 + 0x14, 0, 0);
    }
    return obj;
}
