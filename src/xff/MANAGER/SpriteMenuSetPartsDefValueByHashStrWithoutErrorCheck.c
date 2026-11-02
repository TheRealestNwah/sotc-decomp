typedef struct { int a; int hash; } LayerDef;
typedef struct { LayerDef *def; char *parts; unsigned int flags; char pad[0x38]; } Layer;
typedef struct { int a; int hash; char pad[4]; int value; } PartDef;
typedef struct { PartDef *def; char pad[0x18]; } Part;

extern int MakeStrHashValue(const char *);

void SpriteMenuSetPartsDefValueByHashStrWithoutErrorCheck(unsigned char *o, const char *layerName, const char *partName, int value)
{
    Layer *r = 0;
    Part *p = 0;
    PartDef *def = 0;
    unsigned char *c = o[8] == 0x21 ? o + 0x90 : 0;
    int layerHash = MakeStrHashValue(layerName);
    int partHash = MakeStrHashValue(partName);
    int i;

    for (i = 0; i < *(int *)(c + 8); i++) {
        r = &(*(Layer **)(c + 4))[i];
        if (r->def->hash == layerHash)
            break;
    }
    for (i = 0; i < (int)((r->flags >> 4) & 0x3FF); i++) {
        p = &((Part *)r->parts)[i];
        if (p->def->hash == partHash)
            break;
    }
    if (p)
        def = p->def;
    if (def)
        def->value = value;
}
