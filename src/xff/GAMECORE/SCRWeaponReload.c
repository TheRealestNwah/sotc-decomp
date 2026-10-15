extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_00078C58(void *character);

void SCRWeaponReload(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00078C58);
}
