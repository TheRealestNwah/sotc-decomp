extern void *isysGetThisSubThread(void);
extern char D_0017B5D8[];
extern void bootTexAlphaAnim(void *, void *, float, float);
void nico_yamoriArmLeftTexStart(void)
{
    bootTexAlphaAnim(isysGetThisSubThread(), D_0017B5D8, 1.0f, 0.05f);
}
