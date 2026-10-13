typedef struct LayoutObj LayoutObj;

extern void ForceUnparentLayoutObj(LayoutObj *obj);
extern void CallLayoutObjDebugResetFunc(LayoutObj *obj);
extern void ResetCharacterObj(LayoutObj *obj);

typedef struct {
    char pad0[0x168];
    float fadeTime;
} GcGlobalVar;

extern GcGlobalVar gcGlobalVar;

typedef struct {
    float startTime;
    float endTime;
    float startValue;
    float endValue;
    float value;
} FadeParam;

typedef struct {
    char pad0[0x3C];
    float f3C;
    float f40;
    float f44;
    float f48;
    float f4C;
} LookAtParam;

typedef struct {
    char pad0[0x3CA4];
    int f3CA4;
    int f3CA8;
    int f3CAC;
} PathEx;

void ResetObject(LayoutObj *obj)
{
    ForceUnparentLayoutObj(obj);
    CallLayoutObjDebugResetFunc(obj);
    ResetCharacterObj(obj);
}

void GAMEUTIL_set_parameter_look_at_vs_offset(LookAtParam *p, float a, float b, float c, float d,
                                              float e)
{
    p->f3C = a * 0.0174532925f;
    p->f40 = b * 0.0174532925f;
    p->f44 = c * 0.0174532925f;
    p->f48 = d;
    p->f4C = e;
}

void calcFadeParam(FadeParam *f)
{
    float t = gcGlobalVar.fadeTime;

    if (t <= f->endTime) {
        f->value = f->startValue
                 + (f->endValue - f->startValue) * ((t - f->startTime) / (f->endTime - f->startTime));
    } else {
        f->value = f->endValue;
    }
}

int getPathExFinish(PathEx *p, int kind)
{
    switch (kind) {
    case 2:
    case 3:
    case 4:
        return p->f3CA8;
    case 5:
    case 6:
    case 7:
    case 8:
        return p->f3CA4;
    case 9:
        return p->f3CAC;
    }
    return 0;
}


