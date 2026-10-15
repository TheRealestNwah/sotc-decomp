extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_0007DBF0(void *character);

void SCRWeaponHand(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_0007DBF0);
}
