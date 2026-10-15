extern int func_00055610();
extern void *D_00136AF0;
extern int D_00136AF4;

void SetCharacterObjMotionJumpSpeedLimit(void *obj, int limit)
{
    D_00136AF0 = func_00055610;
    D_00136AF4 = limit;
}
