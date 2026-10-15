extern void iosInverseMatrix(float *, void *);
extern float GetRateInOutCubeVolumeWithInverseMatrix(float *, void *, void *, void *);

float GetRateInOutCubeVolume(void *m, void *a, void *b, void *c)
{
    float inv[16] __attribute__((aligned(16)));
    iosInverseMatrix(inv, m);
    return GetRateInOutCubeVolumeWithInverseMatrix(inv, a, b, c);
}
