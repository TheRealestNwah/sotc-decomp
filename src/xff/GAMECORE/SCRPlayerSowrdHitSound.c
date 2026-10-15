extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void T_00079ED8(void *character);

void SCRPlayerSowrdHitSound(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_00079ED8);
}
