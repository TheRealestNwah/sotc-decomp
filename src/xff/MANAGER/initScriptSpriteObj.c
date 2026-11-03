extern int *DldSysUndefSymbol;

typedef struct {
    int unk0;
    int *ref;
    int def;
    float f0[5];
    int i0;
    float f1[4];
    int i1;
    int unk38;
    int unk3C;
    int a2;
    int unk44;
    int t0;
    int a3;
    int t1;
    int pad[3];
} ScriptSpriteParam;

typedef struct {
    int unk0;
    unsigned int ref;
    int unk8;
    int unkC;
    int unk10;
    int unk14;
    float f0[5];
    int i0;
    float f1[4];
    int i1;
} ScriptSpriteDesc;

extern void *CreateScriptSpriteObj(void *, int, ScriptSpriteParam);

static inline int *dldObj(int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (int *)t[3] : 0;
}

#ifdef NONMATCHING /* a0/a1 swap in the DldSys resolver; permuter found nothing */
void *initScriptSpriteObj(void *parent, ScriptSpriteDesc *desc, int a2, int a3, int t0, int t1)
{
    ScriptSpriteParam param;
    ScriptSpriteParam tmp;

    tmp.unk0 = desc->unk0;
    tmp.ref = (int *)&desc->ref;
    tmp.def = (int)dldObj((int *)&desc->ref);
    tmp.f0[0] = desc->f0[0];
    tmp.f0[1] = desc->f0[1];
    tmp.f0[2] = desc->f0[2];
    tmp.f0[3] = desc->f0[3];
    tmp.f0[4] = desc->f0[4];
    tmp.i0 = desc->i0;
    tmp.f1[0] = desc->f1[0];
    tmp.f1[1] = desc->f1[1];
    tmp.f1[2] = desc->f1[2];
    tmp.f1[3] = desc->f1[3];
    tmp.i1 = desc->i1;
    tmp.unk38 = desc->unk14;
    tmp.unk3C = desc->unk8;
    tmp.a2 = a2;
    tmp.unk44 = desc->unkC;
    tmp.t0 = t0;
    tmp.a3 = a3;
    tmp.t1 = t1;
    tmp.pad[0] = 0;
    tmp.pad[1] = 0;
    tmp.pad[2] = 0;
    param = tmp;
    return CreateScriptSpriteObj(parent, desc->unk10, param);
}
#endif
