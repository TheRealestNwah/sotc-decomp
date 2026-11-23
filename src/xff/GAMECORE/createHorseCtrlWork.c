typedef int s128 __attribute__((mode(TI)));
typedef union { unsigned int w; float f; } CW;
extern int *DldSysUndefSymbol;
extern void setAttainRadPathWork(void *, float);
extern void func_0010A6E8(void *, void *);
extern void _setStopCtrlModeBaseMoveWork(void *, void *);
extern void analyzeMotionProperty(void *, void *, float *, float *, float, float, int);

static inline int *dldData(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (int *)t[4] : 0;
}

static inline char *dldResolveRe(CW *h)
{
    int off = h->w & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((h->w >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

typedef struct {
    CW rad, unk4, unk8, unkC, unk10, unk14, unk18, unk1C, unk20, unk24, unk28, unk2C, unk30, unk34, unk38, unk3C, unk40;
} HorseParam;

typedef struct {
    char pad0[0x64];
    float unk64, unk68, unk6C, unk70, unk74;
    int unk78, unk7C, unk80;
    float unk84, unk88, unk8C;
    int unk90, unk94, unk98, unk9C;
    char padA0[0xB0 - 0xA0];
    int unkB0, unkB4;
    char padB8[0xC0 - 0xB8];
    s128 unkC0;
    int unkD0;
} HorseCtrl;

void createHorseCtrlWork(void *w, HorseCtrl *ctrl, unsigned int *h, void *path)
{
    HorseParam *o = (HorseParam *)dldData(h);
    float sp[2];

    setAttainRadPathWork(path, 3.14159251f);
    func_0010A6E8(w, ctrl);
    ctrl->unk78 = (int)dldResolveRe(&o->unk4);
    ctrl->unk7C = (int)dldResolveRe(&o->unk8);
    ctrl->unk80 = (int)dldResolveRe(&o->unkC);
    ctrl->unkB0 = (int)dldResolveRe(&o->unk3C);
    ctrl->unkB4 = (int)dldResolveRe(&o->unk40);
    asm volatile("sqc2 $vf0, 0(%0)" : : "r"(&ctrl->unkC0) : "memory");
    ctrl->unkD0 = 0;
    ctrl->unk64 = o->rad.f * 0.017453293f;
    ctrl->unk84 = o->unk10.f;
    _setStopCtrlModeBaseMoveWork(ctrl, dldResolveRe(&o->unk14));
    ctrl->unk90 = (int)dldResolveRe(&o->unk18);
    ctrl->unk94 = (int)dldResolveRe(&o->unk1C);
    ctrl->unk98 = (int)dldResolveRe(&o->unk20);
    ctrl->unk9C = (int)dldResolveRe(&o->unk24);
    ctrl->unk68 = o->unk28.f;
    ctrl->unk6C = o->unk2C.f;
    ctrl->unk70 = o->unk30.f;
    ctrl->unk74 = o->unk34.f;
    if (dldResolveRe(&o->unk38) != 0) {
        float r;
        analyzeMotionProperty(w, dldResolveRe(&o->unk38), &sp[0], &sp[1], 1.0f, 0.0f, 0);
        r = sp[0] / sp[1];
        ctrl->unk88 = ((float *)ctrl->unk80)[3] * r;
        ctrl->unk8C = ((float *)ctrl->unk80)[0] * r;
    }
}
