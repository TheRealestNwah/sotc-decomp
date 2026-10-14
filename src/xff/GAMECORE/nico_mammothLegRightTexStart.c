extern void *isysGetThisSubThread(void);
extern char D_0017AC10[];
extern void bootTexAlphaAnim(void *, void *, float, float);
void nico_mammothLegRightTexStart(void)
{
    bootTexAlphaAnim(isysGetThisSubThread(), D_0017AC10, 1.0f, 0.05f);
}
