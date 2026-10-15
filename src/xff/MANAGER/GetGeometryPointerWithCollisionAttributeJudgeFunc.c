extern float ZeroPoint[];
extern void *GetLayoutObjCollisionDBWithTargetAttributeJudgeFunc(void *, void *, void *, void *);
extern void MakeGeometryPointerCollisionInfo(void *, float *, void *, float, float);

void *GetGeometryPointerWithCollisionAttributeJudgeFunc(void *g, void *a, void *b, void *c)
{
    char buf[0x10] __attribute__((aligned(16)));
    void *db = GetLayoutObjCollisionDBWithTargetAttributeJudgeFunc(buf, a, b, c);
    if (db != 0)
        MakeGeometryPointerCollisionInfo(g, ZeroPoint, buf, 0.0f, 0.0f);
    return db;
}
