extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_00056860[];

void SCRGuardArrowShoot(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_00056860);
}
