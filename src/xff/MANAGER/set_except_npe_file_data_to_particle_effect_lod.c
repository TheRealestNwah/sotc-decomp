typedef struct {
    char pad0[0x8];
    int file_data;
    char pad1[0x1BC - 0xC];
} ParticleLodEntry;

typedef struct {
    char pad0[0xD0];
    int count;
    int entries;
    int npe;
} ParticleEffectLod;

int set_except_npe_file_data_to_particle_effect_lod(ParticleEffectLod *lod, int file_data, int unused, int npe)
{
    int i;

    for (i = 0; i < lod->count; i++) {
        ((ParticleLodEntry *)lod->entries)[i].file_data = -1;
    }
    if (lod->count > 0) {
        ((ParticleLodEntry *)lod->entries)[0].file_data = file_data;
    }
    lod->npe = npe;
    return 1;
}
