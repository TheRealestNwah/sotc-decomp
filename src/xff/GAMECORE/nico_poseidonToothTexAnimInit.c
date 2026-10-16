extern void *isysGetThisSubThread(void);
extern void bootTexAlphaAnim(void *, void *, float, float);
extern int D_0017AEE0[], D_0017AEF8[], D_0017AEC8[];

void nico_poseidonToothTexAnimInit(void)
{
    void *th = isysGetThisSubThread();

    bootTexAlphaAnim(th, D_0017AEE0, 0.0f, -0.05f);
    bootTexAlphaAnim(th, D_0017AEF8, 0.0f, -0.05f);
    bootTexAlphaAnim(th, D_0017AEC8, 0.0f, -0.05f);
}
