extern void *func_0001B9A8(int *);
extern char IdentityQuaternion[];
extern char ZeroPoint[];
extern void SetGeometryPointerNodePosState(void *, void *, int, void *, void *);

void getStageLayoutGeometryPointer(void *g)
{
    int t[4];
    void *n = func_0001B9A8(t);
    SetGeometryPointerNodePosState(g, n, t[0], IdentityQuaternion, ZeroPoint);
}
