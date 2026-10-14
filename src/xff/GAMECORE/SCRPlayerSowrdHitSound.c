extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char T_00079ED8[1];

void SCRPlayerSowrdHitSound(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_00079ED8);
}
