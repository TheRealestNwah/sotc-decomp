extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char T_0007A2F8[1];

void SCRPlayerSowrdDiveHitSound(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_0007A2F8);
}
