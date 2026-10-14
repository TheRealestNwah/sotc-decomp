extern void *isysGetThisSubThread(void);
extern char D_0017ABE0[];
extern void bootTexAlphaAnim(void *, void *, float, float);
void nico_mammothArmRightTexStart(void)
{
    bootTexAlphaAnim(isysGetThisSubThread(), D_0017ABE0, 1.0f, 0.05f);
}
