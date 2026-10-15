extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));

extern void T_000794E0(void *character);

void SCRArrowContinue(void *character)
{
    RequestCharacterMotionShiftFunc(character, T_000794E0);
}
