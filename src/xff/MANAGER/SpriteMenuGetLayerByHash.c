typedef struct { int a; int hash; } LayerDef;
typedef struct { LayerDef *def; char pad[0x40]; } Layer;

Layer *SpriteMenuGetLayerByHash(unsigned char *o, int hash)
{
    unsigned char *c = o[8] == 0x21 ? o + 0x90 : 0;
    Layer *r = 0;
    int i;
    for (i = 0; i < *(int *)(c + 8); i++) {
        r = &(*(Layer **)(c + 4))[i];
        if (r->def->hash == hash)
            break;
    }
    return r;
}
