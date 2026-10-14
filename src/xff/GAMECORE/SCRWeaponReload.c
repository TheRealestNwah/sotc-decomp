extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char func_00078C58[1];

void SCRWeaponReload(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00078C58);
}
