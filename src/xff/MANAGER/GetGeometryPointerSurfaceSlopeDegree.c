extern float YUnitVector[];
extern float *GetCollisionDBPlane(void *);
extern float GetPlaneSlopeDegree(float *);

float GetGeometryPointerSurfaceSlopeDegree(char *g)
{
    void *db;
    float *r;
    switch (*(unsigned int *)(g + 0x30)) {
    case 2:
    case 3:
    case 4:
    case 5:
        db = g;
        break;
    case 0:
    case 1:
    case 6:
    case 7:
    case 8:
        db = 0;
        break;
    default:
        db = 0;
        break;
    }
    r = YUnitVector;
    if (db != 0)
        r = GetCollisionDBPlane(db);
    return GetPlaneSlopeDegree(r);
}
