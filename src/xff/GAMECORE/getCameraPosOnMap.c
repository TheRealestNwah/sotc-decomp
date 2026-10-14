typedef union {
    int i;
    float f;
} Word;

typedef struct {
    char pad0[0x28];
    Word columns;
    Word rows;
    char pad30[0x20];
    float width;
    float depth;
} StageMap;

typedef struct {
    char pad0[0x340];
    float camera[4];
} GlobalVar;

extern StageMap D_0017A340;
extern GlobalVar gcGlobalVar;

void getCameraPosOnMap(float *x, float *z)
{
    StageMap *map = &D_0017A340;
    float *cam = gcGlobalVar.camera;

    *x = -cam[0] * map->columns.i / map->width;
    *z = -cam[2] * map->rows.i / map->depth;
}
