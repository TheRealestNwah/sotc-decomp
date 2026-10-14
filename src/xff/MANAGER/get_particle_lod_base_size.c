extern void *iosgluGetCameraContext(void);
extern float GetScreenRadiusParticle(void *, float, float);
float get_particle_lod_base_size(char *p)
{
    return GetScreenRadiusParticle(iosgluGetCameraContext(), *(float *)(p + 0x130), 1.0f);
}
