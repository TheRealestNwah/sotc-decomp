typedef struct EnvelopeLight {
    char pad0[0x2C];
    int flags;
    signed char type;
    char pad31[0xF];
} EnvelopeLight;

typedef struct EnvelopeLightSet {
    EnvelopeLight light[3];
} EnvelopeLightSet;

typedef struct EnvelopeDef {
    char pad0[0x24];
    int type;
} EnvelopeDef;

int IsEnvelopeDistantLightType(EnvelopeLightSet *set, EnvelopeDef *def)
{
    EnvelopeLight *light = 0;
    int i;

    for (i = 0; i < 3; i++) {
        if (set->light[i].type == def->type) {
            light = &set->light[i];
            break;
        }
    }
    if (light->flags & 0x20000) {
        return 1;
    }
    return 0;
}
