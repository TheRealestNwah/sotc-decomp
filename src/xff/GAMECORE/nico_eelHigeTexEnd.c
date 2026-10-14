extern void *isysGetThisSubThread(void);
extern char D_0017B318[];
extern void bootTexAlphaAnim(void *, void *, float, float);
void nico_eelHigeTexEnd(void)
{
    bootTexAlphaAnim(isysGetThisSubThread(), D_0017B318, 0.0f, -0.05f);
}
