extern void *isysGetThisSubThread(void);
extern char D_0017AC28[];
extern void bootTexAlphaAnim(void *, void *, float, float);
void nico_mammothLegLeftTexStart(void)
{
    bootTexAlphaAnim(isysGetThisSubThread(), D_0017AC28, 1.0f, 0.05f);
}
