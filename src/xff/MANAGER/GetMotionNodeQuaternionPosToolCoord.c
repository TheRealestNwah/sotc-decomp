extern void func_00031210(void *, void *, void *, void *, int, int);

void GetMotionNodeQuaternionPosToolCoord(void *quaternion, void *position,
                                       void *object, int node, int toolCoordinates)
{
    func_00031210(quaternion, position, 0, object, node, toolCoordinates);
}
