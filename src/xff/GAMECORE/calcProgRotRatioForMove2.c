typedef struct {
    char pad0[0x78];
    float ratio;
} MoveParam;

typedef struct {
    MoveParam *param;
} MoveWork;

typedef struct {
    char pad0[0x1C];
    MoveWork *work;
    char pad20[0xA4 - 0x20];
    float a4;
    float a8;
} Obj;

typedef struct {
    char pad0[0x190];
    float rotScale;
} GlobalVar;

extern GlobalVar gcGlobalVar;
extern float calcProgRotRatio(float, float, float, float, float);

float calcProgRotRatioForMove2(Obj *obj, float t)
{
    return calcProgRotRatio(t, obj->a4, gcGlobalVar.rotScale, obj->a8, obj->work->param->ratio);
}
