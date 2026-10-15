extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void T_0007A038(void *character);

void SCRPlayerSowrdHitSoundMiddle(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_0007A038);
}
