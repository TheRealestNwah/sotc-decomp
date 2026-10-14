extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_0007DBF0[1];

void SCRWeaponHand(void *character)
{
    RequestCharacterMotionShiftFunc(character, &D_0007DBF0);
}
