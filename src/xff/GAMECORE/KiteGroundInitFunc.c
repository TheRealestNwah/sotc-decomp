typedef int s128 __attribute__((mode(TI)));

typedef struct {
    char pad0[0x24];
    float scale;
    float size;
    char pad2C[8];
} AnimalType;

typedef struct {
    char pad0[0x10];
    AnimalType *types;
} AnimalTypeTable;

typedef struct {
    char pad0[0x14];
    short type;
    char pad16[8];
    unsigned short flags;
    float height;
} KiteParam;

typedef struct {
    int a;
    float b;
    int c;
    int d;
} GeomArg;

extern AnimalTypeTable SH_SmallAnimalTypeDEFAULT;
extern s128 ZeroPoint;
extern float YUnitVector[];
extern void memset(void *, int, int);
extern void *AI_GetGeometryPointerOfLayout(void *, KiteParam *, GeomArg *, float, float, float);
extern float iosGetRandom(void);
extern void SetQuaternionByAxisRotateVWithNoRegularize(float *, short, float *);

void *KiteGroundInitFunc(s128 *pos, float *rot, void *layout, KiteParam *p, int flag)
{
    GeomArg arg;
    AnimalType *types;
    float scale;
    void *g;

    memset(&arg, 0, sizeof(arg));
    arg.b = -1.0f;
    types = SH_SmallAnimalTypeDEFAULT.types;
    if (types == 0)
        return 0;
    if (p == 0)
        return 0;
    if ((unsigned short)(p->flags & 1) && !flag)
        scale = 0.0f;
    else
        scale = types[p->type].scale;
    g = AI_GetGeometryPointerOfLayout(layout, p, &arg, scale * types[p->type].size, scale, p->height);
    if (g == 0)
        return 0;
    *pos = ZeroPoint;
    SetQuaternionByAxisRotateVWithNoRegularize(rot, iosGetRandom() * 3.1415926f * 2.0f * 32768.0f / 3.1415926f, YUnitVector);
    return g;
}
