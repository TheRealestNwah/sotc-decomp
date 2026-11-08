typedef float Vec4[4] __attribute__((aligned(16)));
typedef struct { long long x, y; } Pair;

extern int *DldSysUndefSymbol;
extern char *StageLayout_PLAYER_PARACHUTE;
extern char rootPtn[];
extern char *GetSCRCharaAIWorkPtr(int);
extern void unloadObj(int);
extern void nico_ResetCharacterObjFallDownInfo(int);
extern void getStageLayoutGeometryPointer(void *, int, void *);
extern void GetQuaternionByDegEulerYXZ(void *, float, float, float);
extern int loadObj(void *, void *, void *, int, int, int);

typedef struct {
    int w0;
    void *p4;
    void *p8;
    void *pC;
    int w10;
    int w14;
    float f18;
    int w1C;
    void *p20;
    int w24;
    int w28;
    int w2C;
    int w30;
    int w34;
    int w38;
} LoadDesc;

/* Parked: about 40 words differ (float store scheduling around the vb0/a0 copy). */
#ifdef NONMATCHING
void nico_createPlayerParachute(int chara)
{
    struct { LoadDesc d; char pad[4]; char geo[0x40]; Vec4 v80; Vec4 q90; Vec4 a0; Vec4 vb0; } L;
    char *work = GetSCRCharaAIWorkPtr(chara);
    char *lay;
    char *h;
    int res;
    int *slot;
    unsigned int v;
    int off;
    int *t;

    slot = (int *)(GetSCRCharaAIWorkPtr(chara) + 0x1C60);
    if (*slot != 0) {
        unloadObj(*slot);
        *slot = 0;
    }
    nico_ResetCharacterObjFallDownInfo(chara);
    lay = StageLayout_PLAYER_PARACHUTE;
    getStageLayoutGeometryPointer(L.geo, chara, lay + 0x10);
    L.vb0[0] = *(float *)(lay + 0x30);
    L.vb0[1] = *(float *)(lay + 0x34);
    L.vb0[3] = 1.0f;
    L.vb0[2] = *(float *)(lay + 0x38);
    __asm__ __volatile__("" ::: "memory");
    *(Pair *)L.a0 = *(Pair *)L.vb0;
    L.v80[0] = -*(float *)(lay + 0x18);
    L.v80[1] = *(float *)(lay + 0x1C);
    L.v80[3] = 1.0f;
    L.v80[2] = -*(float *)(lay + 0x20);
    GetQuaternionByDegEulerYXZ(L.q90, *(float *)(lay + 0x24), -*(float *)(lay + 0x28), *(float *)(lay + 0x2C));
    h = lay + 4;
    L.d.w0 = 0;
    L.d.p4 = L.v80;
    L.d.p8 = L.q90;
    L.d.pC = L.a0;
    L.d.w10 = *(int *)(lay + 8);
    L.d.w14 = 0;
    L.d.f18 = *(float *)(lay + 0x40);
    L.d.w1C = *(int *)(lay + 0x44);
    L.d.p20 = L.geo;
    res = 0;
    t = 0;
    v = *(unsigned int *)h;
    off = v & 0x3FFFF;
    if (off != 0)
        t = *(int **)(h - off);
    if (t != 0 && t != DldSysUndefSymbol)
        res = t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3];
    L.d.w24 = res;
    L.d.w2C = 1;
    L.d.w28 = 0;
    L.d.w30 = *(int *)(lay + 0x14);
    L.d.w34 = 0;
    L.d.w38 = 0;
    *(int *)(work + 0x1C60) = loadObj(h, &L.d, rootPtn, 0, 0, 4);
    nico_ResetCharacterObjFallDownInfo(chara);
}
#else
extern void nico_createPlayerParachute(int chara);
#endif
