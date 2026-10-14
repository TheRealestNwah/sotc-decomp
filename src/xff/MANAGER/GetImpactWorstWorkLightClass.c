typedef struct {
    char pad0[0x38];
    float impact;
} LightClass;

typedef struct {
    char pad0[0x530];
    int count;
    LightClass *lights[1];
} LightManager;

LightClass *GetImpactWorstWorkLightClass(LightManager *mgr)
{
    int n = mgr->count;
    LightClass *worst = mgr->lights[0];
    int i;

    for (i = 1; i < n; i++) {
        if (mgr->lights[i]->impact < worst->impact) {
            worst = mgr->lights[i];
        }
    }
    return worst;
}
