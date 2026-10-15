extern int D_0017AEE0[], D_0017AEC8[];
extern void *isysGetThisSubThread(void);
extern void bootTexAlphaAnim(void *, int *, float, float);

void nico_poseidonToothRTexAnimStrat(void)
{
    void *t = isysGetThisSubThread();
    bootTexAlphaAnim(t, D_0017AEE0, 1.0f, 0.05f);
    bootTexAlphaAnim(t, D_0017AEC8, 0.0f, -0.05f);
}
