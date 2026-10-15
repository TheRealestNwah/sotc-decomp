extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void T_00079AA8(void *character);

void SCRHarpoonLoopStart(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_00079AA8);
}
