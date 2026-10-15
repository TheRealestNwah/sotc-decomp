extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void T_0007A198(void *character);

void SCRPlayerSowrdHitSoundLarge(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_0007A198);
}
