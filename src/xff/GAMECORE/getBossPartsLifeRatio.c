typedef struct {
    int key;
    char pad4[0x18];
    float life;
    char pad20[0x38];
} Part;

typedef struct {
    float damage;
    int b;
} Dmg;

extern char **GetSCRCharaAIWorkPtr(void *);

static inline Part *getPart(void *o, int key)
{
    Part *p = 0;
    char *w = *GetSCRCharaAIWorkPtr(o);
    int i;

    key &= 0x3F0;
    for (i = 0; i < *(int *)(w + 0x54); i++) {
        if (key == (*(Part **)(w + 0x10))[i].key) {
            p = &(*(Part **)(w + 0x10))[i];
            break;
        }
    }
    return p;
}

static inline Dmg *getDmg(void *o, int key)
{
    Dmg *d = 0;
    char *w = *GetSCRCharaAIWorkPtr(o);
    int i;

    for (i = 0; i < *(int *)(w + 0x54); i++) {
        if (key == (*(Part **)(w + 0x10))[i].key) {
            d = (Dmg *)(*(char **)(w + 0xE8) + 0x24) + i;
            break;
        }
    }
    return d;
}

float getBossPartsLifeRatio(void *o, int key)
{
    Part *p = getPart(o, key);
    Dmg *d = getDmg(o, key & 0x3F0);

    if (p != 0) {
        float zero = 0.0f;

        if (p->life != zero)
            return (p->life - d->damage) / p->life;
        return zero;
    }
    return 0.0f;
}
