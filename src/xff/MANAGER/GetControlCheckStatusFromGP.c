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

typedef struct SurfaceStatus {
    int valid;
    float slope;
    unsigned long attribute;
} SurfaceStatus;

typedef struct GroundStatus {
    int valid;
    float height;
} GroundStatus;

typedef struct ControlCheckStatus {
    SurfaceStatus surface;
    GroundStatus ground;
} ControlCheckStatus;

extern Vec4 ZeroVector;
extern int CheckLegalCollisionGP(void *);
extern void GetGeometryPointerSurfaceAttribute(unsigned long *, void *);
extern float GetGeometryPointerSurfaceSlopeDegree(void *, Vec4 *);
extern void GetGeometryPointerPosition(Vec4 *, void *);
extern void *GetGeometryPointerObject(void *);
extern int ClipCollisionDirectCallBackOneObj(ClipResult *, Vec4 *, Vec4 *, void *, int, int, int, int);

void GetControlCheckStatusFromGP(ControlCheckStatus *status, char *gp)
{
    Vec4 position;
    ClipResult result;
    Vec4 end;
    unsigned long attribute;
    GroundStatus *ground = &status->ground;

    status->surface.valid = 0;
    ground->valid = 0;
    if (gp == 0)
        return;
    if (CheckLegalCollisionGP(gp)) {
        GetGeometryPointerSurfaceAttribute(&attribute, gp);
        status->surface.valid = 1;
        status->surface.attribute = attribute;
        status->surface.slope = GetGeometryPointerSurfaceSlopeDegree(gp, &ZeroVector);
    }
    if (*(int *)(gp + 0x30) == 10) {
        GetGeometryPointerPosition(&position, gp);
        ground->valid = 1;
        end.q = position.q;
        end.v.y += -1000.0f;
        if (ClipCollisionDirectCallBackOneObj(&result, &position, &end, GetGeometryPointerObject(gp), 0, 0, 0, 0))
            ground->height = position.v.y - result.point.v.y;
        else
            ground->height = position.v.y - end.v.y;
    }
}
