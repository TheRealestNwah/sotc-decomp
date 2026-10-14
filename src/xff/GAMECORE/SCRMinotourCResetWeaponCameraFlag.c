extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_0006BF40[1];

void SCRMinotourCResetWeaponCameraFlag(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0006BF40);
}
