extern void cameraBlurClearIntensityArray();
extern void solarFlareReset();
extern int D_00136BF0;

void SetLayoutDisplayFlag(int arg0)
{
    solarFlareReset();
    cameraBlurClearIntensityArray();
    D_00136BF0 = arg0;
}
