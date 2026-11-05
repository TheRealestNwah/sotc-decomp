typedef int s128 __attribute__((mode(TI)));

typedef struct {
    char pad0[0x524];
    char free[4];
    char active[4];
    int flags;
} LightColMan;

typedef struct {
    s128 position;
    s128 rotation;
    union {
        unsigned char rgba[4];
        int word;
    } color;
    float intensity;
    float unk28;
    int flags;
    int unk30;
    float unk34;
    unsigned char brightness;
    unsigned char unk39;
    char pad3A[2];
    int savedColor;
    float scaledBrightness;
    float unk44;
    float unk48;
    float unk4C;
    int unk50;
    int unk54;
} GameLight;

extern s128 IdentityQuaternion;
extern LightColMan *GetLightColMan(void);
extern void **isysGroupForFirst(void *, int);
extern void isysGroupForExit(void *, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
extern void _isysDeleteGroup(void *, void *, int);
extern void gluGetLookAtPosition(s128 *, float);
extern unsigned char iosCalcIcolorToBrightness(int);

static inline unsigned char *GetObjWork(unsigned char *obj, int type)
{
    if (obj[8] == type) {
        return obj + 0x20;
    }
    return 0;
}

#ifdef NONMATCHING
/* 58 diffs: the light field stores are scheduled out of source order and the -1.0f and 0.0f constants swap f2/f3 */
int NewCreateGameLightClass(int flags, int arg1)
{
    GameLight *light = 0;
    unsigned char *obj = 0;
    int result = 0;
    LightColMan *man = GetLightColMan();
    void **group;

    for (group = isysGroupForFirst(man->free, 0); group != 0; ) {
        obj = *group;
        light = (GameLight *)GetObjWork(obj, 0x1A);
        isysAddGroupWithLinkParam(obj, man->active, 0, 0);
        _isysDeleteGroup(obj, man->free, 0);
        man->flags |= 4;
        break;
    }
    if (obj != 0)
        isysGroupForExit(obj, 0);
    if (light != 0) {
        s128 pos;
        float f;
        light->flags = flags | 0x90101;
        gluGetLookAtPosition(&pos, 8.0f);
        light->position = pos;
        light->rotation = IdentityQuaternion;
        light->color.rgba[3] = 0xFF;
        light->color.rgba[0] = 0xFF;
        light->color.rgba[1] = 0xFF;
        light->color.rgba[2] = 0xFF;
        light->intensity = 1.0f;
        light->savedColor = light->color.word;
        light->brightness = iosCalcIcolorToBrightness(light->color.word);
        f = light->brightness * light->intensity;
        if (f < 0.0f)
            f = -f;
        light->scaledBrightness = f;
        light->unk39 = 1;
        light->unk28 = 10.0f;
        light->unk34 = 100.0f;
        light->unk30 = arg1;
        light->unk48 = -1.0f;
        light->unk4C = 0.0f;
        light->unk44 = -1.0f;
        light->unk50 = 0;
        light->unk54 = 0;
        result = 1;
    }
    return result;
}
#endif
