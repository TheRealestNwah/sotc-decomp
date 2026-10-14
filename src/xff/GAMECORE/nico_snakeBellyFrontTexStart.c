extern void *isysGetThisSubThread(void);
extern char D_0017AF88[];
extern void bootTexAlphaAnim(void *, void *, float, float);
void nico_snakeBellyFrontTexStart(void)
{
    bootTexAlphaAnim(isysGetThisSubThread(), D_0017AF88, 1.0f, 0.05f);
}
