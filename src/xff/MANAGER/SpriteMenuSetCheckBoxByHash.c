#ifdef NONMATCHING
typedef struct { int a; int hash; } LayerDef;
typedef struct { LayerDef *def; char *parts; unsigned int flags; char pad[0x38]; } Layer;
typedef struct { int a; int hash; char pad[4]; unsigned int value; } PartDef;
typedef struct { PartDef *def; char pad[0x18]; } Part;

int SpriteMenuSetCheckBoxByHash(unsigned char *o, int layerHash, int partHash, unsigned int value)
{
    unsigned char *c = o[8] == 0x21 ? o + 0x90 : 0;
    int idx = -1;
    Layer *r = 0;
    int i;

    for (i = 0; i < *(int *)(c + 8); i++) {
        r = &(*(Layer **)(c + 4))[i];
        if (r->def->hash == layerHash)
            break;
    }
    for (i = 0; i < (int)((r->flags >> 4) & 0x3FF); i++) {
        PartDef *def = ((Part *)r->parts)[i].def;
        if (def->hash == partHash) {
            idx = i;
            if (value < 2)
                def->value = value;
            break;
        }
    }
    return idx;
}
#endif
