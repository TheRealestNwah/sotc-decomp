extern void iosInverseMatrix(float *, void *);
extern float GetRateInOutEllipticalSphereVolumeWithInverseMatrix(float *, void *, void *, void *);

float GetRateInOutEllipticalSphereVolume(void *matrix, void *point, void *inner_radius,
                                        void *outer_radius)
{
    float inverse[16] __attribute__((aligned(16)));
    iosInverseMatrix(inverse, matrix);
    return GetRateInOutEllipticalSphereVolumeWithInverseMatrix(inverse, point, inner_radius,
                                                              outer_radius);
}
