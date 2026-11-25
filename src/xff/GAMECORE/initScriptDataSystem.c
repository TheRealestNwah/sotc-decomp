extern int *DldSysUndefSymbol;

#define I(p, o) (*(int *)((char *)(p) + (o)))
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))
#define S(p, o, v) (*(unsigned int *)((char *)(p) + (o)) = (unsigned int)(v))

extern char *GetSCRCharaAIWorkPtr(void *);
extern char *GetLayoutClass(void *);
extern char *GetScriptClass(void *);
extern int _gameFlagChk(int);
extern void loadRequestMotList(void *, void *);
extern int finishLoadMotList(void *);
extern void scrRunM(int);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern void createEyeWork(void *, void *);
extern void createPerceptionWork(void *, void *);
extern void createUserPathWorkEx(void *, void *, float, float, int);
extern void setSearchRouteMaxAngle(void *, float);
extern void setRouteMinAngle(void *, float);
extern void setPathRayWideParam(void *, float, int);
extern void setStabilizeYPathWork(void *, int);
extern void setAngleStabilizeYPathWork(void *, int);
extern void setRayByRealColPathWork(void *, int);
extern void setPassageWideRayPathWork(void *, int);
extern void setSearchRadius(void *, float);
extern void createFastLegCtrlWork(void *, void *, void *, void *);
extern void createSlowLegCtrlWork(void *, void *, void *, void *);
extern void createBirdCtrlWork(void *, void *, void *, void *);
extern void createWormCtrlWork(void *, void *, void *, void *);
extern void initWormIKWork(void *, float);
extern void createBirdCtrl2Work(void *, void *, void *);
extern void createHorseCtrlWork(void *, void *, void *, void *);
extern void initGazeCtrlWork(void *);
extern void execSCRBaseFunc(void *, void *);
extern void createHintWork(void *, void *);
extern void createAngryWork(void *, void *);
extern void createArrowThrustWork(void *, void *, void *);
extern void SetScriptObjDeleteCallBackFunc2(void *, void *, int);
extern void func_0011BDF8();

static inline int *dldTable(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    return off != 0 ? *(int **)((char *)h - off) : 0;
}

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static inline char *dldData(unsigned int *h)
{
    int *t = dldTable(h);

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] : 0;
}

static inline char *dldBase(unsigned int *h)
{
    int *t = dldTable(h);

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t : 0;
}

static inline char *dldResolveB(unsigned int *h)
{
    int *t = (*h & 0x3FFFF) != 0 ? *(int **)((char *)h - (*h & 0x3FFFF)) : 0;

    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((*h >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

#define R(h) dldResolve((unsigned int *)(h))

void initScriptDataSystem(void *obj, unsigned int *h)
{
    char *d;
    char *ai;
    char *mot;
    char *motf;
    char *lay;
    char *lp;
    char *p;
    char *q;
    char *sd;
    int on;

    d = dldData(h);
    ai = (char *)(((unsigned int)GetSCRCharaAIWorkPtr(obj) + 0x13) & ~0xF);
    if (d == 0)
        return;
    I(ai, 0x4090) = I(d, 0);
    S(ai, 0x4178, d + 0x34);
    S(ai, 0x4174, d + 0x30);
    S(ai, 0x417C, d + 0x28);
    mot = d + 0x24;
    S(ai, 0x4180, mot);
    S(ai, 0x416C, R(d + 0x18));
    S(ai, 0x4170, R(d + 0x1C));
    I(ai, 0x4094) = 0;
    I(ai, 0x4098) = 0;
    I(ai, 0x409C) = 0;
    I(ai, 0x40A0) = 0;
    on = 0;
    if (R(d + 0x10) != 0) {
        lay = GetLayoutClass(obj) != 0 ? P(GetLayoutClass(obj), 0x1A4) : 0;
        if (lay != 0) {
            lp = lay + 0x10;
            if (R(lp) != 0) {
                lp = R(lay + 0x10);
                if (dldResolveB((unsigned int *)lp) != 0 && _gameFlagChk(I(R(lp), 0x1C)) != 0) {
                    S(ai, 0x40A0, R(d + 0x10));
                    on = 1;
                }
            }
        }
    }
    if (I(ai, 0x40A0) == 0)
        S(ai, 0x40A0, R(d + 0xC));
    I(ai, 0x4198) = on;

    motf = 0;
    if (on != 0 && R(mot) != 0) {
        loadRequestMotList(obj, mot);
        motf = mot;
    } else if (R(d + 0x20) != 0) {
        loadRequestMotList(obj, d + 0x20);
        motf = d + 0x20;
    }
    if (motf != 0) {
        while (finishLoadMotList(motf) == 0)
            scrRunM(1);
    }

    if (on != 0) {
        q = R(d + 0x14);
        if (q != 0)
            CharaCtrlSetScriptCtrlStatus(obj, I(q, 4));
    }
    if (on != 0 && R(d + 0x40) != 0)
        createEyeWork(obj, d + 0x40);
    else
        createEyeWork(obj, d + 0x3C);
    I(ai, 0x40A4) = 0;
    I(ai, 0x40B0) = 1;
    I(ai, 0x40A8) = 0;
    createPerceptionWork(obj, R(d + 8));

    if (R(d + 4) != 0) {
        p = R(d + 4);
        createUserPathWorkEx(obj, ai, F(p, 0), F(p, 4), I(p, 0x2C));
        setSearchRouteMaxAngle(ai, F(p, 8) * 0.017453293f);
        setRouteMinAngle(ai, (180.0f - F(p, 0xC)) * 0.017453293f);
        setPathRayWideParam(ai, F(p, 0x10), (int)F(p, 0x14));
        setStabilizeYPathWork(ai, I(p, 0x24));
        setAngleStabilizeYPathWork(ai, I(p, 0x28));
        setRayByRealColPathWork(ai, I(p, 0x18));
        setPassageWideRayPathWork(ai, I(p, 0x20));
        setSearchRadius(ai, F(p, 0x1C));
    } else {
        createUserPathWorkEx(obj, ai, 1.0f, 1.0f, 0);
    }

    switch (I(ai, 0x4090)) {
    case 0:
        createFastLegCtrlWork(obj, ai + 0x3D10, P(GetScriptClass(obj), 0x44), ai);
        break;
    case 1:
        createSlowLegCtrlWork(obj, ai + 0x3D10, P(GetScriptClass(obj), 0x44), ai);
        break;
    case 2:
        createBirdCtrlWork(obj, ai + 0x3D10, P(GetScriptClass(obj), 0x44), ai);
        break;
    case 3:
        createWormCtrlWork(obj, ai + 0x3D10, P(GetScriptClass(obj), 0x44), ai);
        initWormIKWork(obj, 3.1415926f);
        break;
    case 4:
        sd = dldData((unsigned int *)P(GetScriptClass(obj), 0x44));
        createSlowLegCtrlWork(obj, ai + 0x3D10, sd, ai);
        createBirdCtrlWork(obj, ai + 0x3DC0, sd + 4, ai);
        break;
    case 5:
        createBirdCtrl2Work(obj, ai + 0x3D10, P(GetScriptClass(obj), 0x44));
        break;
    case 6:
        createHorseCtrlWork(obj, ai + 0x3D10, P(GetScriptClass(obj), 0x44), ai);
        break;
    case -1:
        break;
    }

    initGazeCtrlWork(ai + 0x3CC0);
    *(long long *)(ai + 0x4190) = 0;
    I(ai, 0x40B8) = 0;
    I(ai, 0x40BC) = 0;
    execSCRBaseFunc(obj, d + 0x2C);
    I(ai, 0x40D8) = 0;
    I(ai, 0x40DC) = 0;
    S(ai, 0x4160, R(d + 0x4C));
    createHintWork(obj, d + 0x48);
    createAngryWork(obj, d + 0x38);
    createArrowThrustWork(obj, ai + 0x4184, dldBase((unsigned int *)(d + 0x50)));
    S(ai, 0x4164, R(d + 0x44));
    SetScriptObjDeleteCallBackFunc2(obj, func_0011BDF8, 0);
    scrRunM(1);

}
