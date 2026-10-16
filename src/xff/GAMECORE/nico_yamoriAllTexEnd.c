extern char D_0017B5C0[];
extern char D_0017B5D8[];
extern char D_0017B5F0[];
extern char D_0017B608[];
extern void *isysGetThisSubThread(void);
extern void bootTexAlphaAnim(void *, void *, float, float);

void nico_yamoriAllTexEnd(void)
{
    void *th = isysGetThisSubThread();

    bootTexAlphaAnim(th, D_0017B5C0, 0.0f, -0.05f);
    bootTexAlphaAnim(th, D_0017B5D8, 0.0f, -0.05f);
    bootTexAlphaAnim(th, D_0017B5F0, 0.0f, -0.05f);
    bootTexAlphaAnim(th, D_0017B608, 0.0f, -0.05f);
}
