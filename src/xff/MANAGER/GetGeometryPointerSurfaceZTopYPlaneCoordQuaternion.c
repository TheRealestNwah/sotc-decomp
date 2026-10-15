extern float YUnitVector[];
extern float *GetCollisionDBPlane(char *);
extern void GetPlaneZTopYPlaneCoordQuaternion(void *, float *);

void GetGeometryPointerSurfaceZTopYPlaneCoordQuaternion(void *out, char *g)
{
    char *p;
    float *v;
    switch (*(int *)(g + 0x30)) {
    case 2:
    case 3:
    case 4:
    case 5:
        p = g;
        break;
    case 0:
    case 1:
    case 6:
    case 7:
    case 8:
    default:
        p = 0;
        break;
    }
    v = YUnitVector;
    if (p != 0)
        v = GetCollisionDBPlane(p);
    GetPlaneZTopYPlaneCoordQuaternion(out, v);
}
