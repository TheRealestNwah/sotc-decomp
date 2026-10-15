extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_0007D9B0(void *character);

void SCRPlayerFullPowerAndHp(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_0007D9B0);
}
