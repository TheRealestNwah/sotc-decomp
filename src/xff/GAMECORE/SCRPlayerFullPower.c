extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_0007D998(void *character);

void SCRPlayerFullPower(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_0007D998);
}
