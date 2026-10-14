extern void *isysGetThisSubThread(void);
extern char D_0017AFA0[];
extern void bootTexAlphaAnim(void *, void *, float, float);
void nico_snakeBellyCenterTexStart(void)
{
    bootTexAlphaAnim(isysGetThisSubThread(), D_0017AFA0, 1.0f, 0.05f);
}
