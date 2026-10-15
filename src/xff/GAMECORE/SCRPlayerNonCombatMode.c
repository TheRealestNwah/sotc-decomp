extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_0007DA20(void *character);

void SCRPlayerNonCombatMode(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_0007DA20);
}
