extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char T_0007A198[1];

void SCRPlayerSowrdHitSoundLarge(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_0007A198);
}
