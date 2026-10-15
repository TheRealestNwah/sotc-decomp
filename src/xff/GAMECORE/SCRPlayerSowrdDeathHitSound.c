extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void T_00079D68(void *character);

void SCRPlayerSowrdDeathHitSound(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_00079D68);
}
