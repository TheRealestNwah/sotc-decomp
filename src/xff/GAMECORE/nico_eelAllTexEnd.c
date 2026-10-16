extern char D_0017B288[];
extern char D_0017B2A0[];
extern char D_0017B2B8[];
extern char D_0017B2D0[];
extern char D_0017B2E8[];
extern char D_0017B300[];
extern void *isysGetThisSubThread(void);
extern void bootTexAlphaAnim(void *, void *, float, float);

void nico_eelAllTexEnd(void)
{
    void *th = isysGetThisSubThread();

    bootTexAlphaAnim(th, D_0017B288, 0.0f, -0.05f);
    bootTexAlphaAnim(th, D_0017B2A0, 0.0f, -0.05f);
    bootTexAlphaAnim(th, D_0017B2B8, 0.0f, -0.05f);
    bootTexAlphaAnim(th, D_0017B2D0, 0.0f, -0.05f);
    bootTexAlphaAnim(th, D_0017B2E8, 0.0f, -0.05f);
    bootTexAlphaAnim(th, D_0017B300, 0.0f, -0.05f);
}
