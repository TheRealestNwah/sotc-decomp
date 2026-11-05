typedef struct FsBlur {
    int pad0;
    int count;
} FsBlur;

typedef struct FsFog {
    int pad0;
    float nearDist;
    float farDist;
    float nearRate;
    float farRate;
    int r;
    int g;
    int b;
    int offset;
} FsFog;

typedef struct FsEffectState {
    FsBlur *blur;
    FsFog *fog;
} FsEffectState;

extern FsEffectState D_001303E0;
extern void cameraBlurClearIntensityArray(FsBlur *);
extern void func_0000CF40(FsBlur *);
extern float *getFogNearDist(void);
extern float *getFogFarDist(void);
extern float *getFogNearRate(void);
extern float *getFogFarRate(void);
extern int *getFogColorR(void);
extern int *getFogColorG(void);
extern int *getFogColorB(void);
extern int *getFogOffset(void);
extern void changeFogParam(void);

void effectSet(void)
{
    FsFog *fog;

    if (D_001303E0.blur != 0) {
        if (D_001303E0.blur->count * 16 > 0x630)
            cameraBlurClearIntensityArray(D_001303E0.blur);
        func_0000CF40(D_001303E0.blur);
    }
    fog = D_001303E0.fog;
    if (fog == 0)
        return;
    if (fog->nearDist != -1.0f)
        *getFogNearDist() = fog->nearDist;
    if (fog->farDist != -1.0f)
        *getFogFarDist() = fog->farDist;
    if (fog->nearRate != -1.0f)
        *getFogNearRate() = fog->nearRate;
    if (fog->farRate != -1.0f)
        *getFogFarRate() = fog->farRate;
    if (fog->r != -1)
        *getFogColorR() = fog->r;
    if (fog->g != -1)
        *getFogColorG() = fog->g;
    if (fog->b != -1)
        *getFogColorB() = fog->b;
    if (fog->offset != -1)
        *getFogOffset() = fog->offset;
    changeFogParam();
}
