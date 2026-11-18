typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    Vec4 a;
    Vec4 b;
    Vec4 dir;
    float mtx[16];
} DischargeArc;

typedef struct {
    float scale;
    float ratio;
    int n;
    DischargeArc *arcs;
    int lws;
} DischargeWork;

typedef struct {
    Vec4 color;
    float pad10;
    float maxSize;
    float minSize;
    float height;
    float len;
    float tipScale;
} DischargeData;

typedef struct {
    Vec4 pos;
    Vec4 color;
    Vec4 uv;
} PtclVtx;

extern DischargeWork *getSpecialEffectObjWork(void *);
extern DischargeData *getEditWorkInitData(int);
extern void SCRSetLWSGeometry(int, int, void *, void *);
extern int GetLayoutClass(int);
extern void SetLayoutClassScaleElem(int, void *, int);
extern char *GetScriptAnimationClass(int);
extern void _SCRStartLWS(int, int, int, int);
extern char *iosgluGetCameraContext(void);
extern int clipByMinMaxCube(Vec4 *, Vec4 *, char *);
extern int *getFogUnderWater(void);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void texTransRequest(int, int, int);
extern void transMicroCode(int);
extern void ptclmanBegin(void);
extern void ptclmanEnd(void);
extern void ptclmanBuildMatPacket(int, float, float);
extern void ptclmanBuildEnvPacket(void *, int, void *, int, int, float);
extern void ptclmanBuildVtxPacket(void *, int);
extern PtclVtx *ptclDisplayListGet(int);
extern void ptclDisplayListPut(int);
extern float iosGetRandom(void);
extern void iosGetSinCosf(void *, float);
extern int DldSysUndefSymbol;
extern char IdentityQuaternion[];
typedef struct { char pad[0x190]; float delta; } GlobalVar;
extern GlobalVar gcGlobalVar;

static inline char *dldResolve(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) : 0;
}

static inline void scaleAdd(Vec4 *out, Vec4 *in, float s, Vec4 *add)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(add) : "memory");
}

typedef struct { float x, y, z, w; } __attribute__((aligned(8))) F4;

#ifdef NONMATCHING /* 2 diffs: the original stores the second scale half (sd $v0,0x28($sp)) before jal GetLayoutClass with lw $a0,0x10($s2) in the delay slot; ours swaps them. Permuter: no gain in ~400 iterations */
void dischargeMain(char *obj)
{
    Vec4 color;
    Vec4 pos;
    F4 scl;
    Vec4 max;
    Vec4 min;
    Vec4 *at = (Vec4 *)(obj + 0x20);
    DischargeWork *w = getSpecialEffectObjWork(obj);
    DischargeData *d = getEditWorkInitData(*(int *)(*(char **)(obj + 0x1C) + 8));
    DischargeArc *arc = w->arcs;
    int n;
    int i;

    n = w->n;
    SCRSetLWSGeometry(w->lws, 0, at, IdentityQuaternion);
    max.f[0] = w->ratio * w->scale;
    max.f[1] = 1.0f;
    max.f[2] = w->ratio * w->scale;
    max.f[3] = 1.0f;
    scl = *(F4 *)&max;
    SetLayoutClassScaleElem(GetLayoutClass(w->lws), &scl, 0);
    if (w->ratio == 0.0f) {
        if (*(signed char *)(GetScriptAnimationClass(w->lws) + 0x364) != 1)
            _SCRStartLWS(w->lws, -1, 1, 0);
        return;
    }
    if (*(signed char *)(GetScriptAnimationClass(w->lws) + 0x364) != 5)
        _SCRStartLWS(w->lws, -1, 5, 0);
    pos.q = at->q;
    pos.f[1] += w->ratio * d->height;
    {
        max.q = pos.q;
        min.q = pos.q;
        min.f[0] -= w->scale;
        min.f[2] -= w->scale;
        max.f[0] += w->scale;
        max.f[2] += w->scale;
        if (clipByMinMaxCube(&min, &max, iosgluGetCameraContext() + 0x5A0) != 0)
            return;
    }
    color.q = d->color.q;
    if (*getFogUnderWater() != 0)
        iosDlPushLayer(0xB);
    else
        iosDlPushLayer(0x16);
    texTransRequest(*(int *)(dldResolve((unsigned int *)(*(char **)(obj + 0x1C) + 0x18)) + 0xC), 0, 0);
    transMicroCode(7);
    {
    F4 env = { 1.0f, 1.0f, 0.0f, 0.0f };
    ptclmanBegin();
    ptclmanBuildMatPacket(1, env.x, env.y);
    ptclmanEnd();
    if (n > 0) {
        i = n;
        do {
            PtclVtx *v = ptclDisplayListGet(2);
            PtclVtx *p = v;

            if (gcGlobalVar.delta != 0.0f) {
                iosGetSinCosf(&arc->a, iosGetRandom() * 6.28318548f);
                iosGetSinCosf(&arc->b, iosGetRandom() * 6.28318548f);
            }
            if (v != 0) {
                scaleAdd(&p->pos, &arc->dir, w->ratio * w->scale, &pos);
                p->pos.f[3] = (d->maxSize - d->minSize) * w->ratio + d->minSize;
                p->color.q = color.q;
                p->uv.q = arc->a.q;
                p++;
                scaleAdd(&p->pos, &arc->dir, w->ratio * w->scale * d->len, &pos);
                p->pos.f[3] = (d->maxSize - d->minSize) * w->ratio + d->minSize;
                p->pos.f[3] *= d->tipScale;
                p->color.q = color.q;
                p->uv.q = arc->b.q;
                ptclDisplayListPut(2);
                ptclmanBegin();
                ptclmanBuildEnvPacket(&env, 2, arc->mtx, 0, 0, 1.0f);
                ptclmanBuildVtxPacket(v, 2);
                ptclmanEnd();
            }
            arc++;
        } while (--i != 0);
    }
    }
    iosDlPopLayer();
}
#endif
