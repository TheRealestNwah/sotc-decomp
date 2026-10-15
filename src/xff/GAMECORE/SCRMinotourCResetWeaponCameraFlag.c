extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_0006BF40(void *character);

void SCRMinotourCResetWeaponCameraFlag(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0006BF40);
}
