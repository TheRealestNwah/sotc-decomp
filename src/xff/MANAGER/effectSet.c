typedef struct FsBlur {
    int pad0;
    int count;
    int flareSw : 5;
    int flareBlur : 9;
    int flareSolarLevel : 9;
    int glowLevel : 9;
    int flareR : 9;
    int flareG : 9;
    int flareB : 9;
    int samplePix;
    int dofSw : 2;
    int dofLevel : 4;
    int dofPlanes : 10;
    short dofNearZ;
    int inWater : 2;
    int refBlurLevel : 3;
    int refractBlendRatio : 9;
    int refractBrightness : 9;
    float refractBlurSpeed;
    float refractBlurSpeedRand;
    float refractBlurLevel;
    float refractBlurLevelRand;
    float refractLengthRatio;
    float specularity;
    int shadowIntensity;
    int mBlur : 9;
    int cameraBlurSw : 2;
    int blurAlsoChara : 2;
    int blurWorkSize : 2;
    int nBlurPlanes : 6;
    int blurIntensity : 8;
    float blurZBase;
    float blurShutterSpeed;
    float blurMinThreshold;
    float blurMaxThreshold;
    float blurXYZRatio;
    float blurCamMoveThreshold;
    int bossBlurLevel : 5;
    int bossR : 9;
    int bossG : 9;
    int bossB : 9;
    short bossBlendRatio;
    short bossOutLine;
    short zFogDivide;
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
extern float *getFogNearDist(void);
extern float *getFogFarDist(void);
extern float *getFogNearRate(void);
extern float *getFogFarRate(void);
extern int *getFogColorR(void);
extern int *getFogColorG(void);
extern int *getFogColorB(void);
extern int *getFogOffset(void);
extern void changeFogParam(void);
extern int *getSolarFlareSw(void);
extern void solarFlareReset(int);
extern int *getSolarFlareBlur(void);
extern int *getSolarFlareSolarLevel(void);
extern int *getSolarGlowLevel(void);
extern int *getSolarFlareColorR(void);
extern int *getSolarFlareColorG(void);
extern int *getSolarFlareColorB(void);
extern int *getSolarFlareSamplePix(void);
extern int *getDepthOfFieldSw(void);
extern int *getDepthOfFieldLevel(void);
extern int *getDepthOfFieldPlanes(void);
extern int *getDepthOfFieldNearZ(void);
extern int *getIsInWater(void);
extern int *getRefBlurLevel(void);
extern float *getRefractBlurSpeed(void);
extern float *getRefractBlurSpeedRand(void);
extern float *getRefractBlurLevel(void);
extern float *getRefractBlurLevelRand(void);
extern int *getRefractLengthRatio(void);
extern int *getRefractBlendRatio(void);
extern int *getRefractBrightness(void);
extern float *getSpecularity(void);
extern int *getShadowIntensity(void);
extern int *getMBlur(void);
extern int *getCameraBlurSw(void);
extern int *getBlurAlsoChara(void);
extern int *getBlurWorkSize(void);
extern int *getNBlurPlanes(void);
extern int *getBlurIntensity(void);
extern float *getBlurZBase(void);
extern float *getBlurMinThreshold(void);
extern float *getBlurMaxThreshold(void);
extern float *getBlurShutterSpeed(void);
extern float *getBlurXYZRatio(void);
extern float *getBlurCamMoveThreshold(void);
extern int *getBossEffectBlurLevel(void);
extern int *getBossEffectColorR(void);
extern int *getBossEffectColorG(void);
extern int *getBossEffectColorB(void);
extern int *getBossEffectBlendRatio(void);
extern int *getBossEffectOutLine(void);
extern int *getFogMode(void);
extern int *getZFogDivide(void);

static void func_0000CF40(FsBlur *p)
{
    if (p->flareSw != -1) {
        int *sw = getSolarFlareSw();
        if (*sw != p->flareSw)
            solarFlareReset(*sw);
        *getSolarFlareSw() = p->flareSw;
    }
    if (p->flareBlur != -1)
        *getSolarFlareBlur() = p->flareBlur;
    if (p->flareSolarLevel != -1)
        *getSolarFlareSolarLevel() = p->flareSolarLevel;
    if (p->glowLevel != -1)
        *getSolarGlowLevel() = p->glowLevel;
    if (p->flareR != -1)
        *getSolarFlareColorR() = p->flareR;
    if (p->flareG != -1)
        *getSolarFlareColorG() = p->flareG;
    if (p->flareB != -1)
        *getSolarFlareColorB() = p->flareB;
    if (p->samplePix != -1)
        *getSolarFlareSamplePix() = p->samplePix;
    if (p->dofSw != -1)
        *getDepthOfFieldSw() = p->dofSw;
    if (p->dofLevel != -1)
        *getDepthOfFieldLevel() = p->dofLevel;
    if (p->dofPlanes != -1)
        *getDepthOfFieldPlanes() = p->dofPlanes;
    if (p->dofNearZ != -1)
        *getDepthOfFieldNearZ() = p->dofNearZ;
    if (p->inWater != -1)
        *getIsInWater() = p->inWater;
    if (p->refBlurLevel != -1)
        *getRefBlurLevel() = p->refBlurLevel;
    if (p->refractBlurSpeed != -1.0f)
        *getRefractBlurSpeed() = p->refractBlurSpeed;
    if (p->refractBlurSpeedRand != -1.0f)
        *getRefractBlurSpeedRand() = p->refractBlurSpeedRand;
    if (p->refractBlurLevel != -1.0f)
        *getRefractBlurLevel() = p->refractBlurLevel;
    if (p->refractBlurLevelRand != -1.0f)
        *getRefractBlurLevelRand() = p->refractBlurLevelRand;
    if (p->refractLengthRatio != -1.0f)
        *getRefractLengthRatio() = p->refractLengthRatio;
    if (p->refractBlendRatio != -1)
        *getRefractBlendRatio() = p->refractBlendRatio;
    if (p->refractBrightness != -1)
        *getRefractBrightness() = p->refractBrightness;
    if (p->specularity != -1.0f)
        *getSpecularity() = p->specularity;
    if (p->shadowIntensity != -1)
        *getShadowIntensity() = p->shadowIntensity;
    if (p->mBlur != -1)
        *getMBlur() = p->mBlur;
    if (p->cameraBlurSw != -1)
        *getCameraBlurSw() = p->cameraBlurSw;
    if (p->blurAlsoChara != -1)
        *getBlurAlsoChara() = p->blurAlsoChara;
    if (p->blurWorkSize != -1)
        *getBlurWorkSize() = p->blurWorkSize;
    if (p->nBlurPlanes != -1)
        *getNBlurPlanes() = p->nBlurPlanes;
    if (p->blurIntensity != -1)
        *getBlurIntensity() = p->blurIntensity;
    if (p->blurZBase != -1.0f)
        *getBlurZBase() = p->blurZBase;
    if (p->blurMinThreshold != -1.0f)
        *getBlurMinThreshold() = p->blurMinThreshold;
    if (p->blurMaxThreshold != -1.0f)
        *getBlurMaxThreshold() = p->blurMaxThreshold;
    if (p->blurShutterSpeed != -1.0f)
        *getBlurShutterSpeed() = p->blurShutterSpeed;
    if (p->blurXYZRatio != -1.0f)
        *getBlurXYZRatio() = p->blurXYZRatio;
    if (p->blurCamMoveThreshold != -1.0f)
        *getBlurCamMoveThreshold() = p->blurCamMoveThreshold;
    if (p->bossBlurLevel != -1)
        *getBossEffectBlurLevel() = p->bossBlurLevel;
    if (p->bossR != -1)
        *getBossEffectColorR() = p->bossR;
    if (p->bossG != -1)
        *getBossEffectColorG() = p->bossG;
    if (p->bossB != -1)
        *getBossEffectColorB() = p->bossB;
    if (p->bossBlendRatio != -1)
        *getBossEffectBlendRatio() = p->bossBlendRatio;
    if (p->bossOutLine != -1)
        *getBossEffectOutLine() = p->bossOutLine;
    if (p->zFogDivide != -1) {
        *getFogMode() = p->zFogDivide > 0;
        *getZFogDivide() = p->zFogDivide;
    }
}


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
