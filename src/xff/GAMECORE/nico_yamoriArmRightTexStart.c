extern void *isysGetThisSubThread(void);
extern char D_0017B5C0[];
extern void bootTexAlphaAnim(void *, void *, float, float);
void nico_yamoriArmRightTexStart(void)
{
    bootTexAlphaAnim(isysGetThisSubThread(), D_0017B5C0, 1.0f, 0.05f);
}
