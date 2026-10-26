extern void GetInverseMatrixFromQuaternionPos(float *out, float *quaternion, float *position);
extern float GetRateInOutEllipticalSphereVolumeWithInverseMatrix(float *, void *, void *, void *);
extern float GetRateInOutCubeVolumeWithInverseMatrix(float *, void *, void *, void *);

int CheckCollisionColClass(void *point, char *collision)
{
    float inverse[16] __attribute__((aligned(16)));
    unsigned int flags;
    int result = 0;

    GetInverseMatrixFromQuaternionPos(inverse, (float *)(collision + 0x10), (float *)collision);
    flags = *(unsigned int *)(collision + 0x40);
    if (flags & 1) {
        float rate = GetRateInOutEllipticalSphereVolumeWithInverseMatrix(
            inverse, point, collision + 0x20, collision + 0x30);
        *(float *)(collision + 0x70) = rate;
        if (rate >= 0.0f)
            result = 1;
    } else if (flags & 2) {
        float rate = GetRateInOutCubeVolumeWithInverseMatrix(
            inverse, point, collision + 0x20, collision + 0x30);
        *(float *)(collision + 0x70) = rate;
        if (rate >= 0.0f)
            result = 1;
    }
    return result;
}
