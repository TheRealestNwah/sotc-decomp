extern void *isysGetThisSubThread(void);
extern char D_0017B608[];
extern void bootTexAlphaAnim(void *, void *, float, float);
void nico_yamoriLegLeftTexStart(void)
{
    bootTexAlphaAnim(isysGetThisSubThread(), D_0017B608, 1.0f, 0.05f);
}
