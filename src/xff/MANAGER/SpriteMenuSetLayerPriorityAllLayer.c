typedef struct { int a; int hash; } LayerDef;
typedef struct { LayerDef *def; char *parts; unsigned int flags; char pad[0x38]; } Layer;

static inline unsigned char *cls(unsigned char *p)
{
    return p[8] == 0x21 ? p + 0x90 : 0;
}

static inline unsigned char *cls2(unsigned char *p)
{
    if (p[8] == 0x21)
        return p + 0x90;
    return 0;
}

void SpriteMenuSetLayerPriorityAllLayer(unsigned char *o, int priority)
{
    unsigned char *c = cls2(o);
    int i;

    for (i = 0; i < *(int *)(c + 8); i++) {
        Layer *r = &(*(Layer **)(cls2(o) + 4))[i];
        r->flags = (r->flags & 0xFFFC3FFF) | ((priority & 0xF) << 14);
    }
}
