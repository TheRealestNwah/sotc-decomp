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

static ParticleParameter *func_000CA9E0(ParticleResource *unused0, ParticleResource *resource,
    ParticleParameter *unused2, int index)
{
    if (resource->count - 1 < index)
        return resource->parameters + resource->count - 1;
    return resource->parameters + index;
}
