extern void RequestCharacterMotionShiftFunc(void *, void *);
extern unsigned char T_00079D68[1];

void SCRPlayerSowrdDeathHitSound(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_00079D68);
}
