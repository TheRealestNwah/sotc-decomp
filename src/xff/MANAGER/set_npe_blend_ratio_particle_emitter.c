typedef struct {
    char pad0[0x16C];
    float blend_ratio;
} ParticleEmitter;

extern ParticleEmitter *get_particle_emitter_from_emitter_id(int);

int set_npe_blend_ratio_particle_emitter(void *unused, int id, float ratio)
{
    ParticleEmitter *e = get_particle_emitter_from_emitter_id(id);

    if (e == 0) {
        return 0;
    }
    e->blend_ratio = ratio;
    return 1;
}
