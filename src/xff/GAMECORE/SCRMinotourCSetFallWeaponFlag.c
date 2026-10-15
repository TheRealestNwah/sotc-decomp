extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_0006BE98(void *character);

void SCRMinotourCSetFallWeaponFlag(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0006BE98);
}
