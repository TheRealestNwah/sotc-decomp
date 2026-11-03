typedef int s128 __attribute__((mode(TI)));

typedef union Vec4 {
    struct {
        float x, y, z, w;
    } v;
    s128 q;
} Vec4;

typedef struct ClipResult {
    char pad0[0x40];
    Vec4 point;
} ClipResult;

typedef struct {
    unsigned short id;
    unsigned short sub;
} SurfId;

typedef struct {
    int mode;
    char pad4[0x3C - 4];
    SurfId *target;
    short *map;
} SurfJudge;

typedef struct {
    char pad0[0x20];
    SurfJudge *judge;
} LayoutWork;

typedef struct {
    char pad0[0x184];
    LayoutWork *work;
} LayoutClass;

extern LayoutClass *GetLayoutClass(void *);
extern long ClipCollisionDirectCallBackOneObj(ClipResult *, Vec4 *, Vec4 *, void *, int, int, void *, int);
extern void *GetGeometryPointerCollisionDB(ClipResult *);
extern int func_000AE060(void *);
extern int func_000AE020();

int Check_InVariableXZSurfJudgeFunc_LowerSurface(float *out, void *obj, Vec4 *pos)
{
    ClipResult result;
    Vec4 end;
    SurfJudge *judge = GetLayoutClass(obj)->work->judge;
    SurfId *target = judge->target;
    int id;

    end.q = pos->q;
    end.v.y += -1000.0f;
    if (out != 0)
        *out = 3.40282347e+38f;
    if (!ClipCollisionDirectCallBackOneObj(&result, pos, &end, obj, 0, 0, func_000AE020, 0))
        return 0;
    id = func_000AE060(GetGeometryPointerCollisionDB(&result));
    if (judge->mode < 4 ? id != target->id : judge->map[id] != target->sub)
        return 0;
    if (out != 0)
        *out = pos->v.y - result.point.v.y;
    return 1;
}
