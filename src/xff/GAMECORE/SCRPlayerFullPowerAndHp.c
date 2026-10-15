extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char D_0007D9B0[];

void SCRPlayerFullPowerAndHp(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_0007D9B0);
}
