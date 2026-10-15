extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void T_00079800(void *character);

void SCRArrowLoopEnd(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_00079800);
}
