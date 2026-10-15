extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));

extern void T_00079978(void *character);

void SCRHarpoonContinue(void *character)
{
    RequestCharacterMotionShiftFunc(character, T_00079978);
}
