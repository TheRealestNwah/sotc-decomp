extern void *isysGetThisSubThread(void);
extern char D_0017AFB8[];
extern void bootTexAlphaAnim(void *, void *, float, float);
void nico_snakeBellyBackTexStart(void)
{
    bootTexAlphaAnim(isysGetThisSubThread(), D_0017AFB8, 1.0f, 0.05f);
}
