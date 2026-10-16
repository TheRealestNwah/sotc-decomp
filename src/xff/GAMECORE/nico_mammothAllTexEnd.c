extern char D_0017ABE0[];
extern char D_0017ABF8[];
extern char D_0017AC10[];
extern char D_0017AC28[];
extern void *isysGetThisSubThread(void);
extern void bootTexAlphaAnim(void *, void *, float, float);

void nico_mammothAllTexEnd(void)
{
    void *th = isysGetThisSubThread();

    bootTexAlphaAnim(th, D_0017ABE0, 0.0f, -0.05f);
    bootTexAlphaAnim(th, D_0017ABF8, 0.0f, -0.05f);
    bootTexAlphaAnim(th, D_0017AC10, 0.0f, -0.05f);
    bootTexAlphaAnim(th, D_0017AC28, 0.0f, -0.05f);
}
