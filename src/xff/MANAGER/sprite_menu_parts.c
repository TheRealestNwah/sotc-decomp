extern int MakeStrHashValue(const char *string);

typedef struct {
    int unk0;
    int hash;
    int unk8;
    int value;
} PartsDef;

typedef struct {
    PartsDef *def;
    int unk4;
    int unk8;
    int value;
    int unk10;
    int unk14;
    unsigned int unk18 : 20;
    unsigned int numFormat : 8;
    unsigned int unk18_28 : 2;
    unsigned int soundSwitch : 2;
} Parts;

typedef struct {
    PartsDef *def;
    Parts *parts;
    unsigned int flag : 4;
    unsigned int nparts : 10;
    unsigned int unk8 : 18;
    char pad[0x38];
} Layer;

static inline unsigned char *getMenu(unsigned char *o)
{
    if (o[8] == 0x21)
        return o + 0x90;
    return 0;
}

static inline Parts *getPartsParam(unsigned char *o, int layerHash, int partsHash)
{
    unsigned char *c = getMenu(o);
    Layer *r = 0;
    int i, j;

    for (i = 0; i < *(int *)(c + 8); i++) {
        r = &(*(Layer **)(c + 4))[i];
        if (r->def->hash == layerHash)
            break;
    }
    for (j = 0; j < r->nparts; j++) {
        if (r->parts[j].def->hash == partsHash)
            return &r->parts[j];
    }
    return 0;
}

static inline PartsDef *getPartsDef(unsigned char *o, int layerHash, int partsHash)
{
    Parts *p = getPartsParam(o, layerHash, partsHash);

    return p ? p->def : 0;
}

Parts *SpriteMenuGetPartsParamByHash(unsigned char *o, int layerHash, int partsHash)
{
    return getPartsParam(o, layerHash, partsHash);
}

Parts *SpriteMenuGetPartsParamByHashStr(unsigned char *o, const char *layer, const char *parts)
{
    int layerHash = MakeStrHashValue(layer);

    return getPartsParam(o, layerHash, MakeStrHashValue(parts));
}

PartsDef *SpriteMenuGetPartsDefByHash(unsigned char *o, int layerHash, int partsHash)
{
    return getPartsDef(o, layerHash, partsHash);
}

PartsDef *SpriteMenuGetPartsDefByHashStr(unsigned char *o, const char *layer, const char *parts)
{
    int layerHash = MakeStrHashValue(layer);

    return getPartsDef(o, layerHash, MakeStrHashValue(parts));
}

int SpriteMenuGetPartsDefValueByHash(unsigned char *o, int layerHash, int partsHash)
{
    return getPartsDef(o, layerHash, partsHash)->value;
}

int SpriteMenuGetPartsDefValueByHashStr(unsigned char *o, const char *layer, const char *parts)
{
    int layerHash = MakeStrHashValue(layer);

    return getPartsDef(o, layerHash, MakeStrHashValue(parts))->value;
}

void SpriteMenuSetPartsDefValueByHash(unsigned char *o, int layerHash, int partsHash, int value)
{
    getPartsDef(o, layerHash, partsHash)->value = value;
}

void SpriteMenuSetPartsDefValueByHashStr(unsigned char *o, const char *layer, const char *parts, int value)
{
    int layerHash = MakeStrHashValue(layer);

    getPartsDef(o, layerHash, MakeStrHashValue(parts))->value = value;
}

void SpriteMenuSetSpriteMenuSoundSwitchByHash(unsigned char *o, int layerHash, int partsHash, int on)
{
    getPartsParam(o, layerHash, partsHash)->soundSwitch = on;
}

void SpriteMenuSetSpriteMenuSoundSwitchByHashStr(unsigned char *o, const char *layer, const char *parts, int on)
{
    int layerHash = MakeStrHashValue(layer);

    getPartsParam(o, layerHash, MakeStrHashValue(parts))->soundSwitch = on;
}

void SpriteMenuSetSliderValueByHash(unsigned char *o, int layerHash, int partsHash, int value)
{
    getPartsParam(o, layerHash, partsHash)->value = value;
}

void SpriteMenuSetSliderValueByHashStr(unsigned char *o, const char *layer, const char *parts, int value)
{
    int layerHash = MakeStrHashValue(layer);

    getPartsParam(o, layerHash, MakeStrHashValue(parts))->value = value;
}

void SpriteMenuSetNumPartsFormatByHash(unsigned char *o, int layerHash, int partsHash, int format)
{
    getPartsParam(o, layerHash, partsHash)->numFormat = format;
}

void SpriteMenuSetNumPartsFormatByHashStr(unsigned char *o, const char *layer, const char *parts, int format)
{
    int layerHash = MakeStrHashValue(layer);

    getPartsParam(o, layerHash, MakeStrHashValue(parts))->numFormat = format;
}
