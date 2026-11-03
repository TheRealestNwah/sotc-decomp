typedef struct {
    int enabled;
    float nearDist;
    float farDist;
    float nearRate;
    float farRate;
    int r;
    int g;
    int b;
    int offset;
} FogParam;

typedef struct {
    char pad[0x10];
    FogParam *fog;
} FogEffect;

extern float *getFogNearDist(void);
extern float *getFogFarDist(void);
extern float *getFogNearRate(void);
extern float *getFogFarRate(void);
extern int *getFogColorR(void);
extern int *getFogColorG(void);
extern int *getFogColorB(void);
extern int *getFogOffset(void);
extern void changeFogParam(void);

void initFogEffect(FogEffect *effect)
{
    FogParam *fog = effect->fog;

    if (fog->enabled == 0) {
        return;
    }
    if (fog->nearDist != -1.0f) {
        *getFogNearDist() = fog->nearDist;
    }
    if (fog->farDist != -1.0f) {
        *getFogFarDist() = fog->farDist;
    }
    if (fog->nearRate != -1.0f) {
        *getFogNearRate() = fog->nearRate;
    }
    if (fog->farRate != -1.0f) {
        *getFogFarRate() = fog->farRate;
    }
    if (fog->r != -1) {
        *getFogColorR() = fog->r;
    }
    if (fog->g != -1) {
        *getFogColorG() = fog->g;
    }
    if (fog->b != -1) {
        *getFogColorB() = fog->b;
    }
    if (fog->offset != -1) {
        *getFogOffset() = fog->offset;
    }
    changeFogParam();
}
