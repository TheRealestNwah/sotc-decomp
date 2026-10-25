extern void func_00031210(void *, void *, void *, void *, int, int);

void GetMotionNodeGeoToolCoord(void *quaternion, void *position, void *scale,
                              void *object, int node, int toolCoordinates)
{
    func_00031210(quaternion, position, scale, object, node, toolCoordinates);
}
