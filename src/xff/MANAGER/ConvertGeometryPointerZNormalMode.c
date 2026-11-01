typedef struct {
    long pad0[6];
    int mode;
    int pad34;
    long pad38;
} GeometryPointer;

extern void GetGeometryPointerPosition(float *, GeometryPointer *);
extern void GetGeometryPointerWithCollisionDBDataGlobalPoint(GeometryPointer *, GeometryPointer *, float *);
extern void iosJumpRecoverPoint(const char *, ...);
extern char D_001408A0[];

void ConvertGeometryPointerZNormalMode(GeometryPointer *dst, GeometryPointer *src)
{
    float pos[4];

    *dst = *src;
    switch (src->mode) {
    case 4:
        GetGeometryPointerPosition(pos, src);
        GetGeometryPointerWithCollisionDBDataGlobalPoint(dst, src, pos);
    case 2:
    case 3:
        dst->mode = 5;
        break;
    case 5:
    case 10:
        break;
    default:
        iosJumpRecoverPoint(D_001408A0, src->mode);
        break;
    }
}
