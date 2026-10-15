extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_0007D9D8(void *character);

void SCRPlayerCombatMode(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_0007D9D8);
}
