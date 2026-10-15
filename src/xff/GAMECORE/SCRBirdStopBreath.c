extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void func_00035438(void *character);

void SCRBirdStopBreath(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00035438);
}
