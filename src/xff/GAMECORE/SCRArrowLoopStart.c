extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void T_00079668(void *character);

void SCRArrowLoopStart(void *character)
{
    RequestCharacterMotionShiftFunc(character, &T_00079668);
}
