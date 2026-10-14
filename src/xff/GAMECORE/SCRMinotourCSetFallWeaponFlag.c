extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_0006BE98[1];

void SCRMinotourCSetFallWeaponFlag(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_0006BE98);
}
