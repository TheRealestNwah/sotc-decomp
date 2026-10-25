typedef int s128 __attribute__((mode(TI)));
extern void func_00031210(void *, void *, void *, void *, int, int);

void GetMotionNodePos(void *position, void *object, int node, int toolCoordinates)
{
    s128 quaternion;
    func_00031210(&quaternion, position, 0, object, node, toolCoordinates);
}
