extern void *isysGetThisSubThread(void);
extern char D_0017ABF8[];
extern void bootTexAlphaAnim(void *, void *, float, float);
void nico_mammothArmLeftTexStart(void)
{
    bootTexAlphaAnim(isysGetThisSubThread(), D_0017ABF8, 1.0f, 0.05f);
}
