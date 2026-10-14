extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char T_0007A038[1];

void SCRPlayerSowrdHitSoundMiddle(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_0007A038);
}
