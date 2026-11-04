typedef struct {
    float a[4];
    float b[4];
    float dir[4];
    float mtx[16];
} DischargeArc;

typedef struct {
    int pad0[2];
    int n;
    DischargeArc *arcs;
    int lws;
    int pad14[3];
    DischargeArc arc[1];
} DischargeWork;

extern DischargeWork *getSpecialEffectObjWork(void *);
extern char *getEditWorkInitData(int);
extern float iosGetSinf(float);
extern float iosGetCosf(float);
extern void iosUnitMatrix(float *);
extern void iosRotMatrixY(float *, float);
extern int _SCRSetupLWS(int, int, void *, void *, int);
extern void _SCRStartLWS(int, int, int, int);
extern int ScriptAnimationObjDef_EEL_THUNDER_CIRCLE;
extern char ZeroPoint[];
extern char IdentityQuaternion[];

void dischargeInit(char *obj)
{
    DischargeWork *w = getSpecialEffectObjWork(obj);
    char *d = getEditWorkInitData(*(int *)(*(char **)(obj + 0x1C) + 8));
    DischargeArc *e;
    int i;

    w->arcs = w->arc;
    w->n = ((union { float f; int i; } *)(d + 0x10))->f;
    for (i = 0, e = w->arcs; i < w->n; i++, e++) {
        float ang = (float)i / (float)w->n * 6.28318524f;

        e->dir[0] = -iosGetSinf(ang);
        e->dir[1] = 0.0f;
        e->dir[2] = iosGetCosf(ang);
        e->dir[3] = 1.0f;
        e->a[0] = 1.0f;
        e->a[1] = 0.0f;
        e->a[2] = 0.0f;
        e->a[3] = 0.0f;
        e->b[0] = 1.0f;
        e->b[1] = 0.0f;
        e->b[2] = 0.0f;
        e->b[3] = 0.0f;
        iosUnitMatrix(e->mtx);
        iosRotMatrixY(e->mtx, -ang);
    }
    w->lws = _SCRSetupLWS(ScriptAnimationObjDef_EEL_THUNDER_CIRCLE, 0, ZeroPoint, IdentityQuaternion, 0);
    _SCRStartLWS(w->lws, -1, 1, 0);
}
