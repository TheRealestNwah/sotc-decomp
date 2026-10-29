typedef struct {
    char pad0[0x180];
    float display;
    char pad184[0x38];
} ParticleParameter;
typedef struct {
    char pad0[0xD0];
    int count;
    ParticleParameter *parameters;
} ParticleResource;

static inline ParticleParameter *get_parameter(ParticleResource *resource, int index)
{
    if (resource->count - 1 < index)
        return resource->parameters + resource->count - 1;
    return resource->parameters + index;
}
static inline void get_blend_weights(float *left, float *right, float blend)
{
    if (blend < 0.0f) {
        *left = blend + 1.0f;
        *right = 0.0f;
    } else if (blend < 1.0f) {
        *left = 1.0f - blend;
        *right = blend;
    } else {
        *left = 0.0f;
        *right = blend;
    }
}
void get_particle_parameter_blend_disp(float *out, ParticleResource *first,
    ParticleResource *second, int index, float blend)
{
    ParticleParameter *left = first->parameters + index;
    if (second != 0) {
        ParticleParameter *right = get_parameter(second, index);
        float leftWeight, rightWeight;
        get_blend_weights(&leftWeight, &rightWeight, blend);
        *out = leftWeight * left->display + rightWeight * right->display;
    } else {
        *out = left->display;
    }
}
