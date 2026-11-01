typedef struct {
    char pad0[0x24];
    int busy;
} CharGeoPre;

typedef struct {
    char pad0[0x1C0];
    CharGeoPre pre;
    char pad1E8[0xCE0 - 0x1E8];
    float y;
    float z;
    float x;
    char valid;
} CharacterClass;

extern int func_00041670(float y, float z);

static inline CharacterClass *characterClass(unsigned char *object)
{
    switch (object[8]) {
    case 9: return (CharacterClass *)(object + 0x90);
    case 0x16: return (CharacterClass *)(object + 0x90);
    default: return 0;
    }
}

int ExecCharaGeometryPreprocess(unsigned char *obj, float x, float y, float z)
{
    CharacterClass *c = characterClass(obj);
    CharGeoPre *pre = &c->pre;

    if (y == 0.0f || pre->busy) {
        return 0;
    }
    if (func_00041670(y, z)) {
        c->valid = 1;
        c->x = x;
        c->y = y;
        c->z = z;
        return 1;
    }
    return 0;
}
