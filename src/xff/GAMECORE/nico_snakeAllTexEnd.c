extern void *isysGetThisSubThread(void);
extern void bootTexAlphaAnim(void *, void *, float, float);
extern int D_0017AF88[], D_0017AFA0[], D_0017AFB8[];

void nico_snakeAllTexEnd(void)
{
    void *th = isysGetThisSubThread();

    bootTexAlphaAnim(th, D_0017AF88, 0.0f, -0.05f);
    bootTexAlphaAnim(th, D_0017AFA0, 0.0f, -0.05f);
    bootTexAlphaAnim(th, D_0017AFB8, 0.0f, -0.05f);
}
