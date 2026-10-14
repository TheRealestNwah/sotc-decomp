extern void *isysGetThisSubThread(void);
extern char D_0017AFB8[];
extern void bootTexAlphaAnim(void *, void *, float, float);
void nico_snakeBellyBackTexEnd(void)
{
    bootTexAlphaAnim(isysGetThisSubThread(), D_0017AFB8, 0.0f, -0.05f);
}
