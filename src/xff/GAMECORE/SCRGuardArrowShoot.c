extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_00056860(void *character);

void SCRGuardArrowShoot(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_00056860);
}
