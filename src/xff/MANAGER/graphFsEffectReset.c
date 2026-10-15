extern int D_0013583C, D_00135838, D_001359B8;
extern float D_001359B0;
extern void effectSet(void);
extern void bgBegin(void);
extern void shadowReset(void);
extern void waterRefractionBegin(float);
extern void refractionBegin(float);
extern void reflectionBegin(float);
extern void depthOfField(void);
extern void bossDeathEffectBegin(float);

void graphFsEffectReset(void)
{
    float *f;
    if (D_0013583C == 0)
        return;
    effectSet();
    if (D_00135838 == 0)
        return;
    if (D_001359B8 != 0)
        return;
    f = &D_001359B0;
    bgBegin();
    shadowReset();
    waterRefractionBegin(*f);
    refractionBegin(*f);
    reflectionBegin(*f);
    depthOfField();
    bossDeathEffectBegin(*f);
    f = 0;
}
