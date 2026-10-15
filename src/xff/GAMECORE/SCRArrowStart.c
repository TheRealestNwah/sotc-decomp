extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
extern void D_0007D648(void *character);

void SCRArrowStart(void *character)
{
    RequestCharacterMotionShiftFunc(character, D_0007D648);
}
