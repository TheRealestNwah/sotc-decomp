typedef struct {
    int key;
    char pad[0x54];
} Part;

typedef struct {
    int a;
    float dmg;
} Dmg;

extern char **GetSCRCharaAIWorkPtr(void *);

float getBossPartsCurDamage(void *o, int key)
{
    char *w = *GetSCRCharaAIWorkPtr(o);
    Dmg *d = 0;
    int i;

    key &= 0x3F0;
    for (i = 0; i < *(int *)(w + 0x54); i++) {
        if (key == (*(Part **)(w + 0x10))[i].key) {
            d = (Dmg *)(*(char **)(w + 0xE8) + 0x24) + i;
            break;
        }
    }
    if (d != 0)
        return d->dmg;
    return 0.0f;
}
