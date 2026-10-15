extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_0007DBA0(void *character);

void SCRWeaponSword(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_0007DBA0);
}
