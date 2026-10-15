extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_0007DBA0[];

void SCRWeaponSword(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_0007DBA0);
}
